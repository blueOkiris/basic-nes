; startup code for cc65/ca65

.import _main
.export __STARTUP__:absolute=1
.export _wait_frame
.exportzp _g_frame_count, _g_input_port_1, _g_input_port_1_prev, _g_input_port_2, _g_input_port_2_prev

; linker-generated symbols

.import __STACK_START__, __STACK_SIZE__
.import __OAM_LOAD__
.include "zeropage.inc"

; definitions
PPU_CTRL      = $2000
PPU_MASK      = $2001
PPU_STATUS    = $2002
OAM_ADDRESS   = $2003
OAM_DMA       = $4014
APU_DMC       = $4010
APU_STATUS    = $4015
APU_FRAME_CTR = $4017
INPUT         = $4016
INPUT_1       = $4016
INPUT_2       = $4017

.segment "ZEROPAGE"

; Frame handling
_g_frame_count:       .res 1
frame_done:        .res 1

; Input handling
_g_input_port_1:       .res 1
_g_input_port_1_prev:   .res 1
_g_input_port_2:       .res 1
_g_input_port_2_prev:   .res 1

; arbitrary-use temp vars
temp1:             .res 1
temp2:             .res 1

.segment "HEADER"

; iNES header
; see http://wiki.nesdev.com/w/index.php/INES

.byte $4e, $45, $53, $1a ; "NES" followed by MS-DOS EOF
.byte $01                ; size of PRG ROM in 16 KiB units
.byte $01                ; size of CHR ROM in 8 KiB units
.byte $00                ; horizontal mirroring, mapper 000 (NROM)
.byte $00                ; mapper 000 (NROM)
.byte $00                ; size of PRG RAM in 8 KiB units
.byte $00                ; NTSC
.byte $00                ; unused
.res 5, $00              ; zero-filled

.segment "STARTUP"

; initialize RAM and jump to C main()
start:
    sei ; ignore IRQs
    cld ; disable decimal mode

    ; disable APU frame IRQs
    ldx #$40
    stx APU_FRAME_CTR

    ; setup stack
    ldx #$ff
    txs

    inx ; x = $00
    stx PPU_CTRL ; disable NMI
    stx PPU_MASK ; disable rendering
    stx APU_DMC  ; disable DMC IRQs

    ; If the user presses reset during vblank, the PPU may reset
    ; with the vblank flag still true. This has about a 1 in 13
    ; chance of happening on NTSC or 2 in 9 on PAL. Clear the
    ; flag now so the @vblankwait1 loop sees an actual vblank.
    bit PPU_STATUS

    ; First of two waits for vertical blank to make sure that the
    ; PPU has stabilized
@vblank_wait_1:
    bit PPU_STATUS
    bpl @vblank_wait_1

    ; We now have about 30,000 cycles to burn before the PPU stabilizes.

    stx APU_STATUS ; disable music channels

    ; We'll fill RAM with $00.
    txa
@clear_ram:
    sta $00,   x
    sta $0100, x
    sta $0200, x
    sta $0300, x
    sta $0400, x
    sta $0500, x
    sta $0600, x
    sta $0700, x
    inx
    bne @clear_ram

    ; Initialize OAM data to have all y coordinates off-screen
    ; e.g. set every fourth byte for the 256 bytes starting at __OAM_LOAD__ to $ef
    lda #$ef
@clear_oam:
    sta __OAM_LOAD__, x

    inx
    inx
    inx
    inx
    bne @clear_oam

    ; Second of two waits for vertical blank to make sure that the
    ; PPU has stabilized
@vblank_wait_2:
    bit PPU_STATUS
    bpl @vblank_wait_2

    ; initialize PPU OAM
    stx OAM_ADDRESS ; $00
    lda #>(__OAM_LOAD__)
    sta OAM_DMA

    ; set the C stack pointer
    lda #<(__STACK_START__ + __STACK_SIZE__)
    sta sp
    lda #>(__STACK_START__ + __STACK_SIZE__)
    sta sp+1

    lda PPU_STATUS ; reset the PPU latch

    jmp _main ; call into our C main()


_wait_frame:
    inc frame_done
@loop:
    lda frame_done
    bne @loop

    jsr input_update

    rts

; Read Standard Controller input
; Keep track of last state to detect button up/down transitions
; Read twice to account for DMC DMA interference
; see http://wiki.nesdev.com/w/index.php/Controller_Reading
; see http://wiki.nesdev.com/w/index.php/Standard_controller#APU_DMC_conflict_glitch
input_update:
    ; store _previous input state
    lda _g_input_port_1
    sta _g_input_port_1_prev
    lda _g_input_port_2
    sta _g_input_port_2_prev

    ; get first reading and save to temp
    jsr input_read
@mismatch:
    lda _g_input_port_1
    sta temp1
    lda _g_input_port_2
    sta temp2

    ; get second reading and compare
    jsr input_read
    lda _g_input_port_1
    cmp temp1
    bne @mismatch
    lda _g_input_port_2
    cmp temp2
    bne @mismatch

    rts

; Read the states of both controllers to _g_input_port_1 and _g_input_port_2
input_read:
    ; strobe controllers
    ldx #$01
    stx INPUT
    dex
    stx INPUT

    ldy #08         ; loop over all 8 buttons
@loop:
    lda INPUT_1     ; read button state
    and #$03        ; mask lowest 2 bits
    cmp #$01        ; set carry bit to button state
    rol _g_input_port_1 ; rotate carry bit into button var
    lda INPUT_2     ; repeat for second controller
    and #$03
    cmp #$01
    rol _g_input_port_2
    dey
    bne @loop

    rts

; NMI handler
; Push OAM changes via DMA, increment frame counter, and release _wait_frame
nmi:
    ; save registers to stack
    pha
    txa
    pha
    tya
    pha

    ; start OAM DMA
    lda #0
    sta OAM_ADDRESS
    lda #>(__OAM_LOAD__)
    sta OAM_DMA

    ; increment frame counter
    inc _g_frame_count

    ; release _wait_frame
    lda #0
    sta frame_done

    ; restore registers and return
    pla
    tay
    pla
    tax
    pla

    rti

; IRQ handler
irq:
    ; do nothing
    rti

.segment "RODATA"

; nothing yet

.segment "VECTORS"

; set interrupt vectors to point to handlers
.word nmi   ;$fffa NMI
.word start ;$fffc Reset
.word irq   ;$fffe IRQ

.segment "CHARS"

; include CHR ROM data
.incbin "../spr/nametable0.chr"
