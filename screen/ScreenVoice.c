#include <stdio.h>
#include "ScreenVoice.h"

#define TAG "Screen Voice"

// 初始化函数
static void ScreenInit() {
    lv_obj_add_event_cb(ui_VoiceBtnBack, ui_event_VoiceBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_VoiceSliderVolume, ui_eventVolumeSlider, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_VoiceSliderTone, ui_eventVolumeSlider, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_VoiceSliderPace, ui_eventVolumeSlider, LV_EVENT_VALUE_CHANGED, NULL);
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit \n");
    ScreenVoice.isActive = true;
    update_time_label(ui_VoiceLabelTime);
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    ScreenVoice.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 100 == 0)
        update_time_label(ui_VoiceLabelTime);
}   

ScreenNode_t ScreenVoice = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_VoiceBtnBack( lv_event_t * e) {
    ScreenVoice.deinit();
    ScreenConfig.reinit();
    _ui_screen_change( &ui_ScreenConfig, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenConfig_screen_init);
}

void ui_eventVolumeSlider(lv_event_t * e) {
    lv_obj_t * sliders[] = {ui_VoiceSliderVolume, ui_VoiceSliderTone, ui_VoiceSliderPace};
    lv_obj_t * labels[] = {ui_VoiceLabelVolume2, ui_VoiceLabelTone2, ui_VoiceLabelPace2};
    lv_obj_t * slider = lv_event_get_target(e);
    int value = lv_slider_get_value(slider); // 获取滑块的当前值
    char buffer[10]; // 用于存放格式化后的字符串，足够存放"100%"和终结字符'\0'
    sprintf(buffer, "%d%%", value); // 将值转换为百分比格式
    for(uint8_t i = 0;i < sizeof(sliders)/sizeof(sliders[0]);i++)
    {
        if(slider == sliders[i])
            lv_label_set_text(labels[i], buffer); // 设置标签的文本
    }
}