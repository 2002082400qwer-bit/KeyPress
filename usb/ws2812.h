#ifndef __WS2812_H__
#define __WS2812_H__

#include "Config.h"
#include "GPIO.h"

#define WS P23
#define	COLOR	255				//亮度，最大255

#define	LED_NUM	18				//LED灯个数
#define	SPI_NUM	(LED_NUM*12)	//LED灯对应SPI字节数

#define	SPIF	0x80		/* SPI传输完成标志。写入1清0。*/
#define	WCOL	0x40		/* SPI写冲突标志。写入1清0。  */

void Ws2812_init();

void send();
void Load_Data();
void Led_clear();
void bsp_ws2812_set_color(u16 index, u32 color);
void bsp_ws2812_HSVtoRGB(double h, double s, double v, u8* r, u8* g, u8* b);
void bsp_ws2812_HSVtoRGB24(double h, double s, double v, u32* rgb);

#endif
