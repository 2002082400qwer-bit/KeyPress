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
  u16 i = 0;
  u32 rgb;
  
  static double hue = 0.0;       // 色相[0, 360)
  static double saturation = 1.0; // 饱和度[0, 1]
  static double value      = 0.9; // 亮度[0, 1]
  
  if(g_key_state_led == 0) return;
  g_key_state_led = 0;
  
  Led_clear();
  
  hue += 10;
  if(hue >= 360) hue = 0;
  bsp_ws2812_HSVtoRGB24(hue, saturation, value, &rgb);
  
  for(i = 0; i < 18; i++){
    if((status & (1L << i)) == 0){
        bsp_ws2812_set_color(i, rgb);
    }
    
  }
  Load_Data();
  send();
}