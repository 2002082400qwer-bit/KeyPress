#include "app.h"
#include "oled.h"
#include "bmp.h"

static void GPIO_config(void) {
    P2_MODE_OUT_OD(GPIO_Pin_4);
    P2_MODE_OUT_OD(GPIO_Pin_5);
    P2PU |= 0x30;
  
    //P32初始化
    P3_MODE_IO_PU(GPIO_Pin_2);
}

u8 last_NUM_state = 0;
void app_i2c_init(){
    GPIO_config();

    OLED_Init();//初始化OLED
    OLED_ColorTurn(0);//0正常显示，1 反色显示

    //欢迎语，先在屏幕中显示，并且将num锁状态装载到last_NUM_state
    last_NUM_state = g_NUM_state;
    
    OLED_ShowString(0, 0, "HELLO", 16);
    OLED_ShowChinese(32,3,0,16);
	OLED_ShowChinese(78,3,1,16);
    OLED_ShowString(90, 0, g_NUM_state ? "NUM" : "num", 16);
}

u8 P32_last_status = 1;
u8 OLED_state = 0;
void app_i2c_task(){
    //NUM状态有改变就刷新一下屏幕
    if((last_NUM_state != g_NUM_state) && (OLED_state == 0)){
        //欢迎语
        OLED_ShowString(0, 0, "HELLO", 16);
        OLED_ShowChinese(32,3,0,16);
        OLED_ShowChinese(78,3,1,16);
        OLED_ShowString(90, 0, g_NUM_state ? "NUM" : "num", 16);
        last_NUM_state = g_NUM_state;
    }
    //P32状态没有改变直接return，否则就进行屏幕任务
    if(P32 == P32_last_status) return;
    P32_last_status = P32;
    
    if(P32 == 1) {
        OLED_state++;
        if(OLED_state > 3) OLED_state = 0;
      
        OLED_Clear();
    }
    //屏幕任务
    switch (OLED_state)
    {
        case 0:
            //欢迎语
            OLED_ShowString(0, 0, "HELLO", 16);
            OLED_ShowChinese(32,3,0,16);
            OLED_ShowChinese(78,3,1,16);
            OLED_ShowString(90, 0, g_NUM_state ? "NUM" : "num", 16);
            last_NUM_state = g_NUM_state;
            break;
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