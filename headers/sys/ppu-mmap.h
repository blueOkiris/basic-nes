#ifndef _PPU_MMAP_H_
#define _PPU_MMAP_H_

// PPU memory addresses
// see http://wiki.nesdev.com/w/index.php/PPU_memory_map
// and http://wiki.nesdev.com/w/index.php/PPU_nametables
// and http://wiki.nesdev.com/w/index.php/PPU_attribute_tables
// and http://wiki.nesdev.com/w/index.php/PPU_palettes#Memory_Map
#define PPU_PATTERN_TABLE_0 0x0000 // pattern table 0
#define PPU_PATTERN_TABLE_1 0x1000 // pattern table 1
#define PPU_NAMETABLE_0     0x2000 // nametable 0
#define PPU_NAMETABLE_1     0x2400 // nametable 1
#define PPU_NAMETABLE_2     0x2800 // nametable 2
#define PPU_NAMETABLE_3     0x2C00 // nametable 3
#define PPU_ATTRIB_TABLE_0  0x23C0 // attribute table for nametable 0
#define PPU_ATTRIB_TABLE_1  0x27C0 // attribute table for nametable 1
#define PPU_ATTRIB_TABLE_2  0x2BC0 // attribute table for nametable 2
#define PPU_ATTRIB_TABLE_3  0x2FC0 // attribute table for nametable 3
#define PPU_PALETTE         0x3F00 // palette memory
#define PPU_PALLETE_BGC     0x3F00 // universal background color
#define PPU_PALETTE_BG_0    0x3F01 // background palette 0
#define PPU_PALETTE_BG_1    0x3F05 // background palette 1
#define PPU_PALETTE_BG_2    0x3F09 // background palette 2
#define PPU_PALETTE_BG_3    0x3F0D // background palette 3
#define PPU_PALETTE_SP_0    0x3F11 // sprite palette 0
#define PPU_PALETTE_SP_1    0x3F15 // sprite palette 1
#define PPU_PALETTE_SP_2    0x3F19 // sprite palette 2
#define PPU_PALETTE_SP_3    0x3F1D // sprite palette 3

#endif
