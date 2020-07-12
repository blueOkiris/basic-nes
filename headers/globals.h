#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <data/color.h>
#include <data/data.h>
#include <sys/ppu-ctrl.h>

// Place the gobal text w/out using vars
#define G_TEXT_X            10
#define G_TEXT_Y            14
#define G_TEXT_OFFSET       (G_TEXT_Y * NUM_COLS + G_TEXT_X)
#define G_TEXT_LEN          14
extern const char g_text[];
extern const char g_blank_text[];

#define G_PALETTE_LEN       32
extern const unsigned char g_palettes[];

#define ATTR_SIZE           4
#define ATTR_OFFSET         ((G_TEXT_Y / 4) * (NUM_COLS / 4) + (G_TEXT_X / 4))
#define G_ATTR_LEN          12
extern const unsigned char g_attributes[];

// Background tiles
#define BLANK_TILE          0x00
#define BORDER_TOP_LEFT     0x01
#define BORDER_TOP_RIGHT    0x02
#define BORDER_BOTTOM_LEFT  0x11
#define BORDER_BOTTOM_RIGHT 0x12
#define BORDER_TOP          0x04
#define BORDER_BOTTOM       0x14
#define BORDER_LEFT         0x03
#define BORDER_RIGHT        0x13

#define SPR_PLAYER          0x10

extern unsigned char g_i, g_j;
extern unsigned char g_attr_offset;
extern game_state_t g_state;

#define MAX_SPRITES         64
#define PLAYER_SPRITE_ID    0
extern sprite_t g_sprites[MAX_SPRITES];

#define NUM_LEVELS          1
#define TEST_ROOM_LEVEL_ID  0
extern const level_t g_levels[NUM_LEVELS];

#endif
