// General setup
#define TV_NTSC 1
#include <sys/ppu-mmap.h>
#include <sys/ppu-ctrl.h>
#include <sys/ram-mmap.h>
#include <data/color.h>
#include <sys/ppu.h>

// Project specific
#include <init.h>
#include <globals.h>
#include <data/data.h>

void init_level(void);
void update(void);
void draw_background(void);
void clear_sprites(void);

/*
 * This uses startup code elsewhere
 * 
 * Assumes:
 *  - memory, ppu, etc in known state by this point
 *  - RAM is zeroed
 *  - rendering, sound, and interrupts disabled
 *  - PPU ready to receive
 */
void main(void) {
    // Initialize sprites
    clear_sprites();

    g_state = TITLE_SCREEN;
    init_level();

    // loop forever
    g_attr_offset = ATTR_SIZE;
    while(1) {
        update();
    }
}

void update(void) {
    wait_frame();
    ppu_reset_scroll();

    switch(g_state) {
        /*
        * Changing color text Demo
        */
        case TITLE_SCREEN:
            if(g_frame_count >= (FRAMES_PER_SEC / 4)) {
                // write attributes
                g_ppu_data = (unsigned char *) g_attributes + g_attr_offset;
                ppu_write();

                // rotate attributes
                g_attr_offset += ATTR_SIZE;
                if(g_attr_offset == G_ATTR_LEN)
                    g_attr_offset = 0;

                ppu_reset_scroll();
                g_frame_count = 0;
            }

            if(g_input_port_1 & BUTTON_START) {
                g_state = TEST_ROOM;

                g_sprites[PLAYER_SPRITE_ID].x = (MAX_X / 2) - (SPRITE_WIDTH / 2);
                g_sprites[PLAYER_SPRITE_ID].y = (MAX_Y / 2) - (SPRITE_HEIGHT / 2) + 24;
                g_sprites[PLAYER_SPRITE_ID].tile_index = SPR_PLAYER;
                g_sprites[PLAYER_SPRITE_ID].attributes = 0;

                init_level();
            }

            break;

        /*
         * Player move demo
         */
        case TEST_ROOM:
            if(g_input_port_1 & BUTTON_UP && g_sprites[PLAYER_SPRITE_ID].y > MIN_Y + SPRITE_HEIGHT) {
                -- g_sprites[PLAYER_SPRITE_ID].y;
            }
            
            if(g_input_port_1 & BUTTON_DOWN && g_sprites[PLAYER_SPRITE_ID].y < MAX_Y - (SPRITE_HEIGHT << 1)) {
                ++ g_sprites[PLAYER_SPRITE_ID].y;
            }
            if(g_input_port_1 & BUTTON_LEFT && g_sprites[PLAYER_SPRITE_ID].x > MIN_X + SPRITE_HEIGHT) {
                -- g_sprites[PLAYER_SPRITE_ID].x;
            }
            
            if(g_input_port_1 & BUTTON_RIGHT && g_sprites[PLAYER_SPRITE_ID].x < MAX_X - (SPRITE_HEIGHT << 1)) {
                ++ g_sprites[PLAYER_SPRITE_ID].x;
            }

            if(g_input_port_1 & BUTTON_SELECT) {
                g_state = TITLE_SCREEN;

                g_sprites[PLAYER_SPRITE_ID].x = 0;
                g_sprites[PLAYER_SPRITE_ID].y = 0;
                g_sprites[PLAYER_SPRITE_ID].tile_index = BLANK_TILE;
                g_sprites[PLAYER_SPRITE_ID].attributes = 0;

                init_level();
            }

            break;
    }
}

void init_level(void) {
    ppu_disable();

    // Write palettes
    // Palette data stored 3F00 through 3F1F
    g_ppu_addr = PPU_PALETTE;
    g_ppu_data = (unsigned char *) g_palettes;
    g_ppu_data_size = G_PALETTE_LEN;
    ppu_write();
    
    // Now copy background tiles that make up message into memory
    // Nametable 0: 2000 through 23FF
    draw_background();

    // Draw background text
    g_ppu_addr = PPU_NAMETABLE_0 + G_TEXT_OFFSET;
    g_ppu_data = (unsigned char *) (g_state == TITLE_SCREEN ? g_text : g_blank_text);
    g_ppu_data_size = G_TEXT_LEN;
    ppu_write();

    // Write attributes
    g_ppu_addr = PPU_ATTRIB_TABLE_0 + ATTR_OFFSET;
    g_ppu_data = (unsigned char *) g_attributes;
    g_ppu_data_size = ATTR_SIZE;
    ppu_write();

    // Turn on rendering
    ppu_reset_scroll();
    ppu_enable();
}

void draw_background(void) {
    PPU_ADDR = (unsigned char) ((PPU_NAMETABLE_0 + NAMETABLE_OFFSET) >> 8);
    PPU_ADDR = (unsigned char) (PPU_NAMETABLE_0 + NAMETABLE_OFFSET);

    for(g_j = 0; g_j < NUM_ROWS; ++g_j) {
        for(g_i = 0; g_i < NUM_COLS; ++g_i) {
            switch(g_state) {
                case TEST_ROOM:
                    PPU_DATA = g_levels[TEST_ROOM_LEVEL_ID].bg[g_j][g_i];
                    break;

                default:
                    PPU_DATA = BLANK_TILE;
            }
        }
    }
}

void clear_sprites(void) {
    for(g_i = 0; g_i < MAX_SPRITES; ++g_i) {
        g_sprites[g_i].attributes = 0;
        g_sprites[g_i].x = 0;
        g_sprites[g_i].y = 0;
        g_sprites[g_i].tile_index = BLANK_TILE;
    }
}
