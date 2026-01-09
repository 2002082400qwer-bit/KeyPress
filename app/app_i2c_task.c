#include "app.h"
#include "oled.h"
#include "bmp.h"

static void GPIO_config(void) {
    P2_MODE_OUT_OD(GPIO_Pin_4);
    P2_MODE_OUT_OD(GPIO_Pin_5);
    P2PU |= 0x30;
}


void app_i2c_init(){
    GPIO_config();

    OLED_Init();//初始化OLED
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(1);//0正常显示 1 屏幕翻转显示

}

void app_i2c_task(){
  
    OLED_ShowString(0, 0, "12345!", 16);
}