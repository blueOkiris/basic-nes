#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <sys/ppu-ctrl.h>

// how nes handles sprites
typedef struct sprite {
    unsigned char y;
    unsigned char tile_index;
    unsigned char attributes;
    unsigned char x;
} sprite_t;

typedef struct level {
    unsigned char bg[NUM_ROWS][NUM_COLS];
} level_t;

typedef enum game_state {
    TITLE_SCREEN,
    TEST_ROOM
} game_state_t;

#endif
