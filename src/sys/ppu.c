#define TV_NTSC 1
#include <sys/ppu-ctrl.h>
#include <sys/ppu-mmap.h>
#include <sys/ram-mmap.h>
#include <sys/ppu.h>
#include <globals.h>

#pragma bss-name(push, "ZEROPAGE")

// Used by write ppu function
unsigned short g_ppu_addr;              // destination of PPU address
unsigned char *g_ppu_data;              // pointer to data to copy
unsigned char g_ppu_data_size;          // # of bytes to copy to PPU

#pragma bss-name(pop)

void ppu_reset_scroll(void) {
    PPU_SCROLL = 0x00;
    PPU_SCROLL = 0x00;
}

void ppu_enable(void) {
    PPU_CTRL =  PPUCTRL_NAMETABLE_0 |   // use nametable 0
                PPUCTRL_BPATTERN_0  |   // background uses pattern table 0
                PPUCTRL_NMI_ON;         // enable NMIs

    PPU_MASK =  PPUMASK_COLOR |         // show colors
                PPUMASK_BSHOW |         // show background
                PPUMASK_L8_BSHOW |      // show tiles at left most 8px
                PPUMASK_SSHOW |         // show sprites
                PPUMASK_L8_SSHOW;       // show sprites at left most 8px
}

void ppu_disable(void) {
    PPU_CTRL = 0x00;
    PPU_MASK = 0x00;
}

void ppu_write(void) {
    PPU_ADDR = (unsigned char) (g_ppu_addr >> 8);
    PPU_ADDR = (unsigned char) (g_ppu_addr);

    for (g_i = 0; g_i < g_ppu_data_size; ++g_i ) {
        PPU_DATA = g_ppu_data[g_i];
    }
}
