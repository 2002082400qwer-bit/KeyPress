#include "Keypress.h"
#include "Gpio.h"

#include "usb.h"
#include "usb_req_class.h"

static void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
    
    GPIO_InitStructure.Pin  = GPIO_Pin_7;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//初始化
    
    GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
    
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;	//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
    
    GPIO_InitStructure.Pin  = GPIO_Pin_2;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
}


void KEYPRESS_INIT(){
    GPIO_config();
    COL1 = COL2 = COL3 = COL4 = COL5 = ROW1 = ROW2 = ROW3 = ROW4 = 1;
}

u32 status = 0xFFFFFFFF;


#define down 0
#define up   1

#define down_last_key_status(pos) ((status & (1L << pos)))
#define up_last_key_status(pos)   ((status & (1L << pos)) == 0)

#define setdown_last_key_status(pos) (status &= (~(1L << pos)))
#define setup_last_key_status(pos)   (status |= (1L << pos))

u8 COL(u8 col) {
    if(col == 0) return COL1;
    if(col == 1) return COL2;
    if(col == 2) return COL3;
    if(col == 3) return COL4;
    if(col == 4) return COL5;
    return 1;
}

void ROW(u8 row) {
    ROW1 = (row == 0)?0:1;
    ROW2 = (row == 1)?0:1;
    ROW3 = (row == 2)?0:1;
    ROW4 = (row == 3)?0:1;
}

u32 SCAN(){
    u8 i=0,j=0,pos = 0;

    P53 = 0;
    for(i=0; i<4; i++) {
        ROW(i);
        NOP1();
        for(j=0; j<((i<2)?5:4); j++) {
            if(i<2) pos = i*5 + j;
            if(i>=2) pos = 10 + (i-2)*4 + j;
            if(COL(j) == down && down_last_key_status(pos)) {
                setdown_last_key_status(pos);
                MK_on_keydown();
            } else if(COL(j) == up && up_last_key_status(pos)) {
                setup_last_key_status(pos);
                MK_on_keyup();
            }
        }
        NOP1();
    }
    return status;
}

//-------------senddata------------
u32 last_states = 0;

u8 key_map[18] = {
     0x53, 0x5F, 0x60, 0x61, 0x57,
     0x56, 0x5C, 0x5D, 0x5E, 0x2A,
     0x38, 0x59, 0x5A, 0x5B,
     0x55, 0x62, 0x37, 0x58
};

void send_scandata(){
    u8 keys[8] = {0};
    u32 i = 0,pos = 2;
    u32 status = SCAN();
    
    if(last_states == status) return;
    
    last_states = status;
        
//    if((status & (1L << 5)) == 0) keys[0] |= 0x01;
//    if((status & (1L << 10)) == 0) keys[1] |= 0x02;
//    if((status & (1L << 14)) == 0) keys[2] |= 0x04;
    
    for(i=0;i<18;i++){
        u8 usage_id = key_map[i];
        
        if((status & (1L << i)) == 0){
            keys[pos++] = usage_id;
        }
        if(pos>7)break;
    }
    
    usb_keyboard_send(keys);
}