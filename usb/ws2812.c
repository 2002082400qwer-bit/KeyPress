#include "ws2812.h"
#include "delay.h"
#include "SPI.h"
#include "NVIC.h"
#include "Switch.h"
#include "string.h"
#include <math.h>

#ifndef fmax
#define fmax(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef fmin
#define fmin(a, b) (((a) < (b)) ? (a) : (b))
#endif


u8	xdata  led_RGB[LED_NUM][3];	//LED对应的RGB，led_buff[i][0]-->绿，led_buff[i][1]-->红，led_buff[i][0]-->蓝.
u8	xdata  led_SPI[SPI_NUM];	  //LED灯对应SPI字节数

static void GPIO_config(void) {
    P2_MODE_OUT_PP(GPIO_Pin_3);
}

static void	SPI_config(void){
  
	SPI_InitTypeDef		SPI_InitStructure;

	SPI_InitStructure.SPI_Enable    = ENABLE;				    //SPI启动    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = ENABLE;				    //片选位     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;			    //移位方向   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;	//主从选择   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;			//时钟相位   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;		//数据边沿   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_8;			//SPI速度    SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_2/SPI_Speed_32
	SPI_Init(&SPI_InitStructure);
	NVIC_SPI_Init(DISABLE,Priority_2);		              //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
	SPI_SW(SPI_P22_P23_P24_P25);	                      //SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32

}

void Ws2812_init(){
  GPIO_config();
  SPI_config();
  
  SPSTAT = SPIF | WCOL;
  
}

void	Load_Data(){
  
	u8	xdata *px;
	u16	i,j;
	u8	k;
	u8	dat;

	for(i=0; i<SPI_NUM; i++)	led_SPI[i] = 0;
	px = &led_RGB[0][0];	                  //首地址
	for(i=0, j=0; i<(LED_NUM * 3); i++)
	{
		dat = *px;
		px++;
		for(k=0; k<4; k++)
		{
			if(dat & 0x80)	led_SPI[j]  = 0xE0;	//数据1
			else			led_SPI[j]  = 0x80;	      //数据0
			if(dat & 0x40)	led_SPI[j] |= 0x0E;	//数据1
			else			led_SPI[j] |= 0x08;	      //数据0
			dat <<= 2;
			j++;
		}
	}
}

void Led_clear(){
  u16 i;
  u8	xdata *px;
  
  px = &led_RGB[0][0];	          //亮度(颜色)首地址
  for(i=0; i<(LED_NUM*3); i++){
    *px = 0;
    px++;
  }
}

void send(){
  u16 i;

  for(i=0; i<SPI_NUM; i++){
    SPDAT = led_SPI[i];           //发送串口数据
    while((SPSTAT & SPIF) == 0)	;	//等待发送完成
    SPSTAT = SPIF + WCOL;			    //清0 SPIF和WCOL标志
	}
}

void bsp_ws2812_set_color(u16 index, u32 color){
  // 分别取出 R, G, B
  u8 R = (color >> 16) & 0xFF;
  u8 G = (color >> 8) & 0xFF;
  u8 B = (color >> 0) & 0xFF;
  
  led_RGB[index][0] = G;
  led_RGB[index][1] = R;
  led_RGB[index][2] = B;
  
}

/**
 * 将HSV颜色模式转成RGB
 * hue：[0, 360)		色相：表示颜色，比如红橙黄绿青蓝紫
 * saturation：[0, 100%]	饱和度：颜色的深浅、浓度、鲜艳程度。如红色可以分为深红、洋红、浅红等。
 * value：[0, 100%]		明度：颜色的强度，明暗
 * 
 */
void bsp_ws2812_HSVtoRGB(double h, double s, double v, u8* r, u8* g, u8* b) {
    double r1, g1, b1;

    double c = v * s;
    double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    h = fmod(h, 360.0); // Ensure h is in the range [0, 360)
    s = fmax(0.0, fmin(1.0, s)); // Clamp s to [0, 1]
    v = fmax(0.0, fmin(1.0, v)); // Clamp v to [0, 1]


    if (h >= 0 && h < 60) {
        r1 = c, g1 = x, b1 = 0;
    } else if (h >= 60 && h < 120) {
        r1 = x, g1 = c, b1 = 0;
    } else if (h >= 120 && h < 180) {
        r1 = 0, g1 = c, b1 = x;
    } else if (h >= 180 && h < 240) {
        r1 = 0, g1 = x, b1 = c;
    } else if (h >= 240 && h < 300) {
        r1 = x, g1 = 0, b1 = c;
    } else {
        r1 = c, g1 = 0, b1 = x;
    }

    *r = (u8)((r1 + m) * 255);
    *g = (u8)((g1 + m) * 255);
    *b = (u8)((b1 + m) * 255);
}

void bsp_ws2812_HSVtoRGB24(double h, double s, double v, u32* rgb) {
    u8 r, g, b;
    bsp_ws2812_HSVtoRGB(h, s, v, &r, &g, &b);
    *rgb = ((u32)r << 16) | ((u32)g << 8) | b;
}