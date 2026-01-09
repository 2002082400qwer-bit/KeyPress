#include "Config.h"
#include "GPIO.h"
#include "Timer.h"
#include "NVIC.h"
#include "delay.h"
#include "usb.h"
#include "usb_req_class.h"
#include "Usb_timer.h"
#include "task.h"
#include "ws2812.h"


void Timer_config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义
    //定时器1做16位自动重装, 中断频率为1000HZ
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//指定工作模式,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_T1Stop
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);			//初值,
    TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
    Timer_Inilize(Timer1,&TIM_InitStructure);				//初始化Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
    NVIC_Timer1_Init(ENABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}


void main() {

    EAXSFR();
    Timer_config();
    usb_init();
    Task_init();
    EA = 1;

    app_wdt_init();//初始化并开启看门狗

    while(1) {
        Task_exec_handler();
      
    }
}