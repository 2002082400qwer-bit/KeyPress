#include "app.h"

void app_ws2812_init(){
  Ws2812_init();
  
  Led_clear();
  Load_Data();
  send();
  Load_Data();
  send();
}

void app_ws2812_task(){
  u8 i = 0;
  static u8 g_color = 0;
  static u8 r_color = 0;
  static u8 b_color = 0;
  
  if(g_key_state_led == 0) return;
  g_key_state_led = 0;
  
  Led_clear();
  
  for(i = 0; i < 18; i++){
    if((status & (1L << i)) == 0){
      led_RGB[i][0] = g_color;
      led_RGB[i][1] = r_color;
      led_RGB[i][2] = b_color;
    }
    if(g_color > 255) g_color = g_color % 100;
    if(r_color > 255) g_color = g_color % 100;
    if(b_color > 255) g_color = g_color % 100;
    g_color += 17;
    r_color += 27;
    b_color += 37;
    
  }
  Load_Data();
  send();
}