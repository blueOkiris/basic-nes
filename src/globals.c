#include <globals.h>

const char g_text[] = "Press Start!!";     // message
const char g_blank_text[] = "             ";

const unsigned char g_palettes[] = {
    COLOR_BLACK,                            // background color

    COLOR_BLUE, COLOR_WHITE, COLOR_RED,     // background palett 0
    0,                                      // ignored
    0, 0, COLOR_GREEN,
    0,                                      // ignored
    0, 0, COLOR_YELLOW,
    0,
    0, 0, COLOR_WHITE,

    COLOR_BLACK,                            // background color (mirror)
 
    // sprite palette 0
    COLOR_BLUE, COLOR_DGRAY, COLOR_MAROON,
    0,
    0, 0, 0,
    0,
    0, 0, 0,
    0,
    0, 0, 0,
};

const unsigned char g_attributes[] = {
    // Layout - 0120123
    0x00,                                   // 00 00 00 00 or 0 0
                                            //                0 0
    0x90,                                   // 10 01 00 00 or 0 0
                                            //                1 2
    0x40,                                   // 01 00 00 00 or 0 0
                                            //                0 1
    0xE0,                                   // 11 10 00 00 or 0 0
                                            //                2 3

    // Layout 2 - 2012013
    0x80, 0x40, 0x20, 0xD0,

    // Layout 3 - 1201203
    0x40, 0x20, 0x90, 0xC0,
};

// Fast mem
#pragma bss-name(push, "ZEROPAGE")

unsigned char g_i, g_j;
unsigned char g_attr_offset;

game_state_t g_state = TEST_ROOM;

#pragma bss-name(pop)

// Sprite mem
#pragma bss-name(push, "OAM")

sprite_t g_sprites[MAX_SPRITES];

#pragma bss-name(pop)
