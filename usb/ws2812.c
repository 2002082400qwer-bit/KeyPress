#include "ws2812.h"
#include "delay.h"
#include "SPI.h"
#include "NVIC.h"
#include	"Switch.h"
#include	"string.h"

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

