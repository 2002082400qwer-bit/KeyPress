#ifndef __APP_H__
#define __APP_H__

#include "Config.h"
#include "Keypress.h"
#include "ws2812.h"

//=================°´¼ü====================

extern u8 g_key_state_led;
extern u32 status;

void App_keypress_init();
void App_keypress_task();

//=================ws2812µÆ================
extern u8	xdata  led_RGB[LED_NUM][3];

void app_ws2812_init();
void app_ws2812_task();

#endif