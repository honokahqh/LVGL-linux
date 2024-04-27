#include <stdio.h>
#include "ScreenRoomWin.h"

#define TAG "Screen Room Win"
// 初始化函数
static void ScreenInit() {
    lv_obj_add_event_cb(ui_RoomWinBtnBack, ui_event_RoomWinBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomWinBtnBack1, ui_event_RoomWinBtnBack, LV_EVENT_CLICKED, NULL);
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit \n");
    ScreenRoomWin.isActive = true;
    update_time_label(ui_RoomWinLabelTime);
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    ScreenRoomWin.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 100 == 0)
        update_time_label(ui_RoomWinLabelTime);
}   

ScreenNode_t ScreenRoomWin = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_RoomWinBtnBack( lv_event_t * e) {
    ScreenRoomWin.deinit();
    ScreenRoomMain.reinit();
    _ui_screen_change( &ui_ScreenRoomMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenRoomMain_screen_init);
}
