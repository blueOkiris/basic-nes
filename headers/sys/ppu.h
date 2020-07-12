#ifndef _PPU_H_
#define _PPU_H_

//#pragma bss-name(push, "ZEROPAGE")

// Used by write ppu function
extern unsigned short g_ppu_addr;           // destination of PPU address
extern unsigned char *g_ppu_data;           // pointer to data to copy
extern unsigned char g_ppu_data_size;       // # of bytes to copy to PPU

//#pragma bss-name(pop)

void ppu_reset_scroll(void);
void ppu_enable(void);
void ppu_write(void);
void ppu_disable(void);

#endif
