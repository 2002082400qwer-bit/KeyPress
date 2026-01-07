/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序 Descriptor       */
/*---------------------------------------------------------------------*/

#include "usb_desc.h"

char code DEVICEDESC[18] =
{
    0x12,                   //bLength(18);
    0x01,                   //bDescriptorType(Device);
    0x00,0x02,              //bcdUSB(2.00);
    0x00,                   //bDeviceClass(0);
    0x00,                   //bDeviceSubClass0);
    0x00,                   //bDeviceProtocol(0);
    0x40,                   //bMaxPacketSize0(64);
    0xbf,0x34,              //idVendor(34bf);
    0x03,0xff,              //idProduct(ff01);
    0x00,0x01,              //bcdDevice(1.00);
    0x01,                   //iManufacturer(1);
    0x02,                   //iProduct(2);
    0x00,                   //iSerialNumber(0);
    0x01,                   //bNumConfigurations(1);
};

char code CONFIGDESC[41] =
{
    0x09,                   //bLength(9);
    0x02,                   //bDescriptorType(Configuration);
    0x29,0x00,              //wTotalLength(41);
    0x01,                   //bNumInterfaces(1);
    0x01,                   //bConfigurationValue(1);
    0x00,                   //iConfiguration(0);
    0x80,                   //bmAttributes(BUSPower);
    0x32,                   //MaxPower(100mA);

    0x09,                   //bLength(9);
    0x04,                   //bDescriptorType(Interface);
    0x00,                   //bInterfaceNumber(0);
    0x00,                   //bAlternateSetting(0);
    0x02,                   //bNumEndpoints(2);
    0x03,                   //bInterfaceClass(HID);
    0x01,                   //bInterfaceSubClass(0);
    0x01,                   //bInterfaceProtocol(0);
    0x00,                   //iInterface(0);

    0x09,                   //bLength(9);
    0x21,                   //bDescriptorType(HID);
    0x01,0x01,              //bcdHID(1.01);
    0x00,                   //bCountryCode(0);
    0x01,                   //bNumDescriptors(1);
    0x22,                   //bDescriptorType(HID Report);
    0x41,0x00,              //wDescriptorLength(65);

    0x07,                   //bLength(7);
    0x05,                   //bDescriptorType(Endpoint);
    0x81,                   //bEndpointAddress(EndPoint1 as IN);
    0x03,                   //bmAttributes(Interrupt);
    0x08,0x00,              //wMaxPacketSize(8);
    0x0a,                   //bInterval(10ms);

    0x07,                   //bLength(7);
    0x05,                   //bDescriptorType(Endpoint);
    0x01,                   //bEndpointAddress(EndPoint1 as OUT);
    0x03,                   //bmAttributes(Interrupt);
    0x01,0x00,              //wMaxPacketSize(1);
    0x0a,                   //bInterval(10ms);
};

/*
Input Report: PC输入
0   Modifierkeys (D0:LCtrl D1:LShift D2:LAlt D3:LGui D4:RCtrl D5:RShift D6:RAlt D7:RGui)
1	Reserved  预留
2	Keycode 1
3	Keycode 2
4	Keycode 3
5	Keycode 4
6	Keycode 5
7	Keycode 6

Output Report: PC输出
0   LEDs (D0:NumLock D1:CapLock D2:ScrollLock)
*/
char code HIDREPORTDESC[65] =
{
    0x05,0x01,              //USAGE_PAGE(Generic Desktop);
    0x09,0x06,              //USAGE(Keyboard);
    0xa1,0x01,              //COLLECTION(Application);
    0x05,0x07,              //  USAGE_PAGE(Keyboard);
    0x19,0xe0,              //  USAGE_MINIMUM(224);
    0x29,0xe7,              //  USAGE_MAXIMUM(231);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);	// 0
    0x25,0x01,              //  LOGICAL_MAXIMUM(1);	// 1
    0x75,0x01,              //  REPORT_SIZE(1);			// 1bit
    0x95,0x08,              //  REPORT_COUNT(8);		// 8个 Modifierkeys
    0x81,0x02,              //  INPUT(Data,Variable,Absolute);
    
    0x75,0x08,              //  REPORT_SIZE(8);			// 8bit
    0x95,0x01,              //  REPORT_COUNT(1);		// 1个 Reserved
    0x81,0x01,              //  INPUT(Constant);
    
    0x19,0x00,              //  USAGE_MINIMUM(0);
    0x29,0x65,              //  USAGE_MAXIMUM(101);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);
    0x25,0x65,              //  LOGICAL_MAXIMUM(101);// Usage ID
    0x75,0x08,              //  REPORT_SIZE(8);			 // 8bit
    0x95,0x06,              //  REPORT_COUNT(6);		 // 6个
    0x81,0x00,              //  INPUT(Data,Array);
    
    0x05,0x08,              //  USAGE_PAGE(LEDs);
    0x19,0x01,              //  USAGE_MINIMUM(1);
    0x29,0x03,              //  USAGE_MAXIMUM(3);
    0x15,0x00,              //  LOGICAL_MINIMUM(0);		// 0
    0x25,0x01,              //  LOGICAL_MAXIMUM(1);		// 1
    0x75,0x01,              //  REPORT_SIZE(1);				// 1bit
    0x95,0x03,              //  REPORT_COUNT(3);			// 3个
    0x91,0x02,              //  OUTPUT(Data,Variable,Absolute);
    
    0x75,0x05,              //  REPORT_SIZE(5);				// 5bit
    0x95,0x01,              //  REPORT_COUNT(1);			// 1个
    0x91,0x01,              //  OUTPUT(Constant);
    
    0xc0,                   //END_COLLECTION;
};

char code LANGIDDESC[10] =
{
    0x04,0x03,
    0x09,0x04,
};

// 数组的元素个数要和头文件保持一致
char code MANUFACTDESC[16] =
{
    0x10,0x03,
    'I',0,
    'T',0,
    'H',0,
    'E',0,
    'I',0,
    'M',0,
    'A',0,
};

// 设置产品名称 https://www.ip138.com/ascii/
// 黑马传智\u9ed1\u9a6c\u4f20\u667a
//萌新\u840C \u65B0
char code PRODUCTDESC[20] =
{
    0x14,0x03,
    'I',0,
    'T',0,
    'C',0,
    'A',0,
    'S',0,
    'T',0,
    '-',0,
    0x0C, 0x84,
    0xB0, 0x65,
};

char code PACKET0[2] = 
{
    0, 0,
};

char code PACKET1[2] = 
{
    1, 0,
};
