#include "task.h"
#include "GPIO.h"

volatile u32 g_task_cnt = 0;

void Task_init(){
  App_keypress_init();
  app_ws2812_init();
}

Task_t task_list[] = {
// task_cnt   task_period   callback
//    {0,         500,        App_Task1},
    {0,          10,        App_keypress_task},
    {0,          10,        app_ws2812_task},
    
};
u8 task_len = sizeof(task_list) / sizeof(task_list[0]);

void Task_switch_handler(void){
    g_task_cnt++;
}

void Task_exec_handler(){
    u8 i = 0;    
    for(i = 0; i < task_len; i++){ 
        Task_t *task = &task_list[i];

        if((u32)(g_task_cnt - task->task_cnt) < task->task_period){
            continue;
        }
        task->task_cnt = g_task_cnt;

        task->callback();
    }
}
