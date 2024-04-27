#include <stdio.h>
#include <time.h>
#include "ScreenMain.h"

#define TAG "Screen main"

static void update_time_labels();

// 初始化函数
static void ScreenInit() {
    ScreenMain.isActive = true;
    LOG_I(TAG, "init.. \n");
    lv_obj_add_event_cb(ui_MainPanelSet, ui_event_MainPanelSet, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MainPanelRoomCtrl, ui_event_MainPanelRoomCtrl, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MainPanelMusic, ui_event_MainPanelMusic, LV_EVENT_CLICKED, NULL);
}

// 初始化函数
static void ScreenReinit() {
    ScreenMain.isActive = true;
    LOG_I(TAG, "reinit \n");
    update_time_labels();
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    ScreenMain.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 5 == 0)
    {
        update_time_labels();
    }
        
}   

ScreenNode_t ScreenMain = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_MainPanelSet( lv_event_t * e) {
    ScreenMain.deinit();
    ScreenConfirm.reinit();
    _ui_screen_change( &ui_ScreenConfirm, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenConfirm_screen_init);
}

void ui_event_MainPanelRoomCtrl( lv_event_t * e) {
    ScreenMain.deinit();
    ScreenRoomMain.reinit();
    _ui_screen_change( &ui_ScreenRoomMain, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenRoomMain_screen_init);
}

void ui_event_MainPanelMusic( lv_event_t * e) {
    ScreenMain.deinit();
    ScreenMusic.reinit();
    _ui_screen_change( &ui_ScreenMusic, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenMusic_screen_init);
}

void update_time_labels(void) {
    static uint32_t i = 0;
    time_t now = time(NULL);
    // 将now调整为东八区时间
    now += 8 * 3600; // 8小时*每小时3600秒
    struct tm *tm_now = gmtime(&now); // 使用gmtime获取UTC时间，并手动调整为东八区

    char time_str[6]; // HH:MM 加上字符串结束符 '\0'
    if(i % 2)
        strftime(time_str, sizeof(time_str), "%H:%M", tm_now);
    else 
        strftime(time_str, sizeof(time_str), "%H %M", tm_now);
    i++;
    lv_label_set_text(ui_MainLabelTime, time_str);

    char day_str[16];
    strftime(day_str, sizeof(day_str), "%m月%d日 %a", tm_now);
    lv_label_set_text(ui_MainLabelDay, day_str);
}