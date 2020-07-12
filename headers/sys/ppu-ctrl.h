#ifndef _PPU_CTRL_H_
#define _PPU_CTRL_H_

// PPU_CTRL flags
// see http://wiki.nesdev.com/w/index.php/PPU_registers#Controller_.28.242000.29_.3E_write
#define PPUCTRL_NAMETABLE_0     0x00    // use nametable 0
#define PPUCTRL_NAMETABLE_1     0x01    // use nametable 1
#define PPUCTRL_NAMETABLE_2     0x02    // use nametable 2
#define PPUCTRL_NAMETABLE_3     0x03    // use nametable 3
#define PPUCTRL_INC_1_HORIZ     0x00    // PPU_DATA increments 1 horizontally
#define PPUCTRL_INC_32_VERT     0x04    // PPU_DATA increments 32 vertically
#define PPUCTRL_SPATTERN_0      0x00    // sprite pattern table 0
#define PPUCTRL_SPATTERN_1      0x08    // sprite pattern table 1
#define PPUCTRL_BPATTERN_0      0x00    // background pattern table 0
#define PPUCTRL_BPATTERN_1      0x10    // background pattern table 1
#define PPUCTRL_SSIZE_8x8       0x00    // 8x8 sprite size
#define PPUCTRL_SSIZE_16x16     0x00    // 16x16 sprite size
#define PPUCTRL_NMI_OFF         0x00    // disable NMIs
#define PPUCTRL_NMI_ON          0x80    // enable NMIs

// PPU_MASK flags
// see http://wiki.nesdev.com/w/index.php/PPU_registers#Mask_.28.242001.29_.3E_write
#define PPUMASK_COLOR           0x00
#define PPUMASK_GRAY            0x01
#define PPUMASK_L8_BHIDE        0x00
#define PPUMASK_L8_BSHOW        0x02
#define PPUMASK_L8_SHIDE        0x00
#define PPUMASK_L8_SSHOW        0x04
#define PPUMASK_BHIDE           0x00
#define PPUMASK_BSHOW           0x08
#define PPUMASK_SHIDE           0x00
#define PPUMASK_SSHOW           0x10
#ifdef TV_NTSC
    #define PPUMASK_EM_RED      0x20
    #define PPUMASK_EM_GREEN    0x40
#else // TV_PAL
    #define PPUMASK_EM_RED      0x40
    #define PPUMASK_EM_GREEN    0x20
#endif
#define PPUMASK_EM_BLUE         0x80

// PPU resolution
// see http://wiki.nesdev.com/w/index.php/PPU_nametables
#define MIN_X                   0
#define MAX_X                   256
#define NUM_COLS                32
#ifdef TV_NTSC
    #define MIN_Y               8
    #define MAX_Y               231
    #define NUM_ROWS            28
    #define FIRST_ROW           1
    #define LAST_ROW            27
#else // TV_PAL
    #define MIN_Y               0
    #define MAX_Y               239
    #define NUM_ROWS            30
    #define FIRST_ROW           0
    #define LAST_ROW            29
#endif
#define NAMETABLE_OFFSET        (NUM_COLS * FIRST_ROW)
#define SPRITE_HEIGHT           8
#define SPRITE_WIDTH            8

// PPU framerate
#ifdef TV_NTSC
    #define FRAMES_PER_SEC      60
#else // TV_PAL
    #define FRAMES_PER_SEC      50
#endif

#endif