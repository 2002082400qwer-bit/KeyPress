#ifndef __TASK_H__
#define __TASK_H__

#include "Config.h"
#include "app.h"

typedef void (*Task_cb)(void);

typedef struct {
    u32 task_cnt;
    u32 task_period;
    Task_cb callback;
} Task_t;

void Task_init();

void Task_switch_handler();

void Task_exec_handler();

#endif