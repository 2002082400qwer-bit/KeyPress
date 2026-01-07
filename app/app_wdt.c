#include "app.h"
#include	"WDT.h"

void	WDT_config()
{
	WDT_InitTypeDef	WDT_InitStructure;					//结构定义

	WDT_InitStructure.WDT_Enable     = ENABLE;					//中断使能   ENABLE或DISABLE
	WDT_InitStructure.WDT_IDLE_Mode  = WDT_IDLE_STOP;		//IDLE模式是否停止计数		WDT_IDLE_STOP,WDT_IDLE_RUN
	WDT_InitStructure.WDT_PS         = WDT_SCALE_16;		//看门狗定时器时钟分频系数		WDT_SCALE_2,WDT_SCALE_4,WDT_SCALE_8,WDT_SCALE_16,WDT_SCALE_32,WDT_SCALE_64,WDT_SCALE_128,WDT_SCALE_256
	WDT_Inilize(&WDT_InitStructure);					//初始化
}

void app_wdt_init(){
  WDT_config();
}

void app_wdt_task(){
  WDT_Clear();    // 喂狗
}

