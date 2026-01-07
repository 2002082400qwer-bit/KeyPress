#include "app.h"
#include "ws2812.h"

#define LED53 P53

u8 g_key_state_led = 0;

void MK_on_keydown(){
    g_key_state_led = 1;
}

void MK_on_keyup(){
    g_key_state_led = 2;
}

void App_keypress_init(){
    KEYPRESS_INIT();
    
}

void App_keypress_task(){
    send_scandata();
}