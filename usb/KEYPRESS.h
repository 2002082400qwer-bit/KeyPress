#ifndef __KEYPRESS_H__
#define __KEYPRESS_H__

#include "Config.h"
#include "GPIO.h"

#define COL1 P17
#define COL2 P03
#define COL3 P06
#define COL4 P40
#define COL5 P52

#define ROW1 P41
#define ROW2 P34
#define ROW3 P35
#define ROW4 P07

extern u32 status;

void KEYPRESS_INIT();

u32 SCAN();

void send_scandata();

extern void MK_on_keydown();
extern void MK_on_keyup();

#endif