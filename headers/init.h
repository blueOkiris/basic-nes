#ifndef _INIT_H_
#define _INIT_H_

extern unsigned char g_frame_count;
#pragma zpsym("g_frame_count");

extern unsigned char g_input_port_1;
#pragma zpsym("g_input_port_1");

extern unsigned char g_input_port_1_prev;
#pragma zpsym("g_input_port_1_prev");

extern unsigned char g_input_port_2;
#pragma zpsym("g_input_port_2");

extern unsigned char g_input_port_2_prev;
#pragma zpsym("g_input_port_2_prev");

#define BUTTON_RIGHT    0x01
#define BUTTON_LEFT     0x02
#define BUTTON_DOWN     0x04
#define BUTTON_UP       0x08
#define BUTTON_START    0x10
#define BUTTON_SELECT   0x20
#define BUTTON_B        0x40
#define BUTTON_A        0x80

void wait_frame(void);

#endif