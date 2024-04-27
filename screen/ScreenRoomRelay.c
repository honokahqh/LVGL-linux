#include <stdio.h>
#include "ScreenRoomRelay.h"

#define TAG "Screen Room Win"

lv_obj_t **relay_btns[] = {&ui_RoomRelayBtnRelay9, &ui_RoomRelayBtnRelay5, &ui_RoomRelayBtnRelay10, &ui_RoomRelayBtnRelay11, 
                            &ui_RoomRelayBtnRelay7, &ui_RoomRelayBtnRelay8, &ui_RoomRelayBtnRelay12, &ui_RoomRelayBtnRelay13};

lv_obj_t **relay_switch[] = {&ui_RoomRelaySwRelay9, &ui_RoomRelaySwRelay5, &ui_RoomRelaySwRelay10, &ui_RoomRelaySwRelay11, 
                            &ui_RoomRelaySwRelay7, &ui_RoomRelaySwRelay8, &ui_RoomRelaySwRelay12, &ui_RoomRelaySwRelay13};                   
// 初始化函数
static void ScreenInit() {
    lv_obj_add_event_cb(ui_RoomRelayBtnBack, ui_event_RoomRelayBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomRelayBtnBack1, ui_event_RoomRelayBtnBack, LV_EVENT_CLICKED, NULL);
    
    for(int i = 0;i < sizeof(relay_btns)/sizeof(relay_btns[0]); i++){
        lv_obj_add_event_cb(*relay_btns[i], ui_event_RoomRelayCtrl, LV_EVENT_CLICKED, NULL);
    }
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit \n");
    ScreenRoomRelay.isActive = true;
    update_time_label(ui_RoomRelayLabelTime);
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    ScreenRoomRelay.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 100 == 0)
        update_time_label(ui_RoomRelayLabelTime);
}   

ScreenNode_t ScreenRoomRelay = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_RoomRelayBtnBack( lv_event_t * e) {
    ScreenRoomRelay.deinit();
    ScreenRoomMain.reinit();
    _ui_screen_change( &ui_ScreenRoomMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenRoomMain_screen_init);
}

void ui_event_RoomRelayCtrl(lv_event_t *e) {
    lv_obj_t *clicked_btn = lv_event_get_target(e);
    for (int i = 0; i < sizeof(relay_btns) / sizeof(relay_btns[0]); i++) {
        if (clicked_btn == *relay_btns[i]) {
            LOG_I(TAG, "Panel %d clicked\n", i);
            bool is_checked = lv_obj_get_state(*relay_switch[i]) & LV_STATE_CHECKED;
            if (is_checked) {
                lv_obj_clear_state(*relay_switch[i], LV_STATE_CHECKED);
            } else {
                lv_obj_add_state(*relay_switch[i], LV_STATE_CHECKED);
            }
            // 触发LV_EVENT_VALUE_CHANGED来启动动画
            lv_event_send(*relay_switch[i], LV_EVENT_VALUE_CHANGED, NULL);
            break; // 如果找到匹配项，不需要继续循环
        }
    }
}
