#include "lvgl_ScreenConfig.h"
#include <time.h>

#define TAG "ScreenMasterCtrl" 

// squareline中不好添加的在此处添加
ScreenNode_t* Screens[] = {&ScreenMain, &ScreenConfirm, &ScreenConfig, &ScreenVoice, &ScreenRoomMain, &ScreenRoomWin, &ScreenRoomRelay,
                                     &ScreenMusic};

void ScreenExtraInit(void)
{
    speaker_init();
    srand(time(NULL));
    for(uint8_t i = 0;i < sizeof(Screens)/sizeof(Screens[i]);i++)
        Screens[i]->init();
}

void ScreenPeriodProcess(void)
{
    static uint64_t count_5ms = 0;
    if(count_5ms % 20 == 0)
    {
        for(uint8_t i = 0;i < sizeof(Screens)/sizeof(Screens[i]);i++)
        {
            if(Screens[i]->isActive)
            {
                Screens[i]->PeriodProcess();
            }
        }
    }
    count_5ms++;
}

void update_time_label(lv_obj_t *label) {
    time_t now = time(NULL);
    // 将now调整为东八区时间
    now += 8 * 3600; // 8小时*每小时3600秒
    struct tm *tm_now = gmtime(&now); // 使用gmtime获取UTC时间，并手动调整为东八区

    char time_str[6]; // HH:MM 加上字符串结束符 '\0'
    strftime(time_str, sizeof(time_str), "%H:%M", tm_now);
    lv_label_set_text(label, time_str);
}
