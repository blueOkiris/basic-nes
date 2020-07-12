#ifndef _RAM_MMAP_H_
#define _RAM_MMAP_H_

#define PPU_CTRL    *((unsigned char *) 0x2000)
#define PPU_MASK    *((unsigned char *) 0x2001)
#define PPU_STATUS  *((unsigned char *) 0x2002)
#define PPU_SCROLL  *((unsigned char *) 0x2005)
#define PPU_ADDR    *((unsigned char *) 0x2006)
#define PPU_DATA    *((unsigned char *) 0x2007)

#endif