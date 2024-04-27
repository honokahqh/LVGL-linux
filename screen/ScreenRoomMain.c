#include <stdio.h>
#include "ScreenRoomMain.h"

#define TAG "Screen Room Main"

RoomMainAircon_t AirconState;
const char *LabelMode[] = {"自动", "制冷", "制热", "送风", "除湿"};
lv_img_dsc_t *IconMode[] = {&ui_img_767853082, &ui_img_1894006371, &ui_img_1902601757, &ui_img_2107464944, &ui_img_1869319599};
lv_img_dsc_t *IconWind[] = {&ui_img_122363411, &ui_img_575592273, &ui_img_117415882, &ui_img_11555231}; // 自动 低 中 高

void Refresh_Aircon_Icon(void);

// 初始化函数
static void ScreenInit() {
    AirconState.temp = 26;
    lv_obj_add_event_cb(ui_RoomMainBtnBack, ui_event_RoomMainBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainPanelWindow, ui_event_RoomMainPanelWindow, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainPanelLight, ui_event_RoomMainPanelLight, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_RoomMainPanelMainSw, ui_event_RoomMainSwitch, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_RoomMainBtnAirconSW, ui_event_RoomMainAirconConfig, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainBtnAirconUp, ui_event_RoomMainAirconConfig, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainBtnAirconDown, ui_event_RoomMainAirconConfig, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainBtnAirconMode, ui_event_RoomMainAirconConfig, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_RoomMainBtnAirconWind, ui_event_RoomMainAirconConfig, LV_EVENT_CLICKED, NULL);
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit \n");
    ScreenRoomMain.isActive = true;
    Refresh_Aircon_Icon();
    update_time_label(ui_RoomMainLabelTime);
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    ScreenRoomMain.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 100 == 0)
        update_time_label(ui_RoomMainLabelTime);
}   

ScreenNode_t ScreenRoomMain = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_RoomMainBtnBack( lv_event_t * e) {
    ScreenRoomMain.deinit();
    ScreenMain.reinit();
    _ui_screen_change( &ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenMain_screen_init);
}

void ui_event_RoomMainPanelWindow( lv_event_t * e) {
    ScreenRoomMain.deinit();
    ScreenRoomWin.reinit();
    _ui_screen_change( &ui_ScreenRoomWin, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenRoomWin_screen_init);
}

void ui_event_RoomMainPanelLight( lv_event_t * e) {
    ScreenRoomMain.deinit();
    ScreenRoomRelay.reinit();
    _ui_screen_change( &ui_ScreenRoomRelay, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenRoomRelay_screen_init);
}

void ui_event_RoomMainSwitch( lv_event_t * e) {
    LOG_I(TAG, "Room Main Switch cliked\n");
    bool is_checked = lv_obj_get_state(ui_RoomMainSw) & LV_STATE_CHECKED;
    if (is_checked) {
        lv_obj_clear_state(ui_RoomMainSw, LV_STATE_CHECKED);
    } else {
        lv_obj_add_state(ui_RoomMainSw, LV_STATE_CHECKED);
    }
    // 触发LV_EVENT_VALUE_CHANGED来启动动画
    lv_event_send(ui_RoomMainSw, LV_EVENT_VALUE_CHANGED, NULL);
}

void ui_event_RoomMainAirconConfig( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * clicked_btn = lv_event_get_target(e);
    lv_obj_t * btn[] = {ui_RoomMainBtnAirconSW, ui_RoomMainBtnAirconUp, ui_RoomMainBtnAirconDown,
                         ui_RoomMainBtnAirconMode, ui_RoomMainBtnAirconWind};
    if ( event_code == LV_EVENT_CLICKED) {
        for(int i = 0;i < sizeof(btn) / sizeof(btn[0]); i++)
        {
            if(clicked_btn == btn[i])
            {
                switch (i)
                {
                case Sw:
                    AirconState.sw = !(AirconState.sw);
                    break;
                case TempUp:
                    AirconState.temp++;
                    if (AirconState.temp > 30)
                        AirconState.temp = 30;
                    break;
                case TempDown:
                    AirconState.temp--;
                    if(AirconState.temp < 16)
                        AirconState.temp = 16;
                    break;
                case Mode:
                    AirconState.mode = (AirconState.mode + 1) % 5;
                    break;
                case Wind:
                    AirconState.wind = (AirconState.wind + 1) % 4;
                    break;
                default:
                    LOG_E(TAG, "%s switch err %d\n", __func__, i);
                    break;
                }
            }
        }
    }
    Refresh_Aircon_Icon();
}

void Refresh_Aircon_Icon(void)
{
    if(AirconState.sw)
    {
        char buffer[4];
        sprintf(buffer, "%d", AirconState.temp / 10);
        lv_label_set_text(ui_RoomMainLabelTemp1, buffer);
        sprintf(buffer, "%d", AirconState.temp % 10);
        lv_label_set_text(ui_RoomMainLabelTemp2, buffer);
    }
    else
    {
        lv_label_set_text(ui_RoomMainLabelTemp1,"-");
        lv_label_set_text(ui_RoomMainLabelTemp2,"-");
    }
    for(uint8_t i = 0;i < 5;i++)
    {
        if(AirconState.mode == i)
        {
            lv_label_set_text( ui_RoomMainLabelAirconMode1, LabelMode[i]);
            lv_obj_set_style_bg_img_src( ui_RoomMainBtnAirconMode, IconMode[i], LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    for(uint8_t i = 0;i < 4;i++)
    {
        if(AirconState.wind == i)
            lv_obj_set_style_bg_img_src( ui_RoomMainBtnAirconWind, IconWind[i], LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}
