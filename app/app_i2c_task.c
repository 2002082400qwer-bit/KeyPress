#include "app.h"
#include "oled.h"
#include "bmp.h"

static void GPIO_config(void) {
    P2_MODE_OUT_OD(GPIO_Pin_4);
    P2_MODE_OUT_OD(GPIO_Pin_5);
    P2PU |= 0x30;
  
    //P32
    P3_MODE_IO_PU(GPIO_Pin_2);
}

void app_i2c_init(){
    GPIO_config();

    OLED_Init();//初始化OLED
    OLED_ColorTurn(0);//0正常显示，1 反色显示

    //欢迎语
    OLED_ShowString(0, 0, "HELLO", 16);
    OLED_ShowChinese(32,3,0,16);
	OLED_ShowChinese(78,3,1,16);
}

u8 P32_last_status = 1;
u8 OLED_state = 0;
void app_i2c_task(){
    if(P32 == P32_last_status) return;
    P32_last_status = P32;
    if(P32 == 1) {
        OLED_state++;
        if(OLED_state > 3) OLED_state = 1;
      
        OLED_Clear();
    }
    
    switch (OLED_state)
    {
    	case 1:
          OLED_DrawBMP(0, 0, 128, 64, &BMP1);
          OLED_ShowChinese(95,2,2,16);
          OLED_ShowChinese(95,5,3,16);
          break;
    	case 2:
          OLED_ShowString(0, 0, "54321!", 16);
          break;
    	case 3:
          OLED_ShowString(0, 0, "hello word!", 16);
          break;
    	default:
          break;
    }
}