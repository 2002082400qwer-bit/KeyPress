#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

#include "Config.h"

//--------------------------------config.h---------------------------

#define FOSC                    24000000UL

#define EN_EP1IN
//#define EN_EP2IN
//#define EN_EP3IN
//#define EN_EP4IN
//#define EN_EP5IN
#define EN_EP1OUT
//#define EN_EP2OUT
//#define EN_EP3OUT
//#define EN_EP4OUT
//#define EN_EP5OUT

#define EP0_SIZE                64

#ifdef EN_EP1IN
#define EP1IN_SIZE              64
#endif
#ifdef EN_EP2IN
#define EP2IN_SIZE              64
#endif
#ifdef EN_EP3IN
#define EP3IN_SIZE              64
#endif
#ifdef EN_EP4IN
#define EP4IN_SIZE              64
#endif
#ifdef EN_EP5IN
#define EP5IN_SIZE              64
#endif
#ifdef EN_EP1OUT
#define EP1OUT_SIZE             64
#endif
#ifdef EN_EP2OUT
#define EP2OUT_SIZE             64
#endif
#ifdef EN_EP3OUT
#define EP3OUT_SIZE             64
#endif
#ifdef EN_EP4OUT
#define EP4OUT_SIZE             64
#endif
#ifdef EN_EP5OUT
#define EP5OUT_SIZE             64
#endif

//--------------------------------stc.h---------------------------

typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned int ushort;
typedef unsigned long ulong;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

#endif