#include "ScreenConfirm.h"

#define TAG "Screen Confirm"
static char key[7];
static int key_len = 0; // 增大到7以存储空字符'\0'

static void ui_ConfirmKeyProcess(uint8_t index);
static void ui_UpdateLabel(void);
static void ui_ClearKey(void);
static void ui_AddKey(char num);

// 初始化函数
static void ScreenInit() {
    lv_obj_add_event_cb(ui_ConfirmBtn0, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn1, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn2, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn3, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn4, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn5, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn6, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn7, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn8, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn9, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtnCancel, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtnConfirm, ui_event_ConfirmInputKey, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtnBack, ui_event_ConfirmBtnBack, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfirmBtnReset, ui_event_ConfirmSysReset, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtnInit, ui_event_ConfirmAppReset, LV_EVENT_CLICKED, NULL);
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit.. \n");
    ScreenConfirm.isActive = true;
    update_time_label(ui_ConfirmLabelTime);
    lv_label_set_text(ui_ConfirmLabelInput, "请输入管理密码");
    key_len = 0;
    key[0] = '\0'; // 清空字符串
}
// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit.. \n");
    ScreenConfirm.isActive = false;
}

static void PeriodProcess() {
    static uint32_t count_100ms = 0;
    if(count_100ms % 100 == 0)
        update_time_label(ui_ConfirmLabelTime);
    count_100ms++;
}   

ScreenNode_t ScreenConfirm = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_ConfirmKeyProcess(uint8_t index) {
    if (index < 10) { // 0~9的按钮
        ui_AddKey('0' + index); // 将数字转换为字符并添加
    } else if (index == 10) { // 取消按钮
        ui_ClearKey();
    } else if (index == 11) { // 确定按钮
        if (strcmp(key, "888888") == 0) {
            // 执行页面跳转逻辑
            ScreenConfirm.deinit();
            ScreenConfig.reinit();
            _ui_screen_change( &ui_ScreenConfig, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenConfig_screen_init);
        } else {
            // 键值不匹配，可执行相应处理，如清空或提示错误
            ui_ClearKey();
        }
    }
}

void ui_event_ConfirmInputKey(lv_event_t * e) {
    lv_obj_t * clicked_btn = lv_event_get_target(e);
    lv_obj_t * panels[] = {ui_ConfirmBtn0, ui_ConfirmBtn1, ui_ConfirmBtn2, ui_ConfirmBtn3, ui_ConfirmBtn4, ui_ConfirmBtn5,
                           ui_ConfirmBtn6, ui_ConfirmBtn7, ui_ConfirmBtn8, ui_ConfirmBtn9, ui_ConfirmBtnCancel, ui_ConfirmBtnConfirm};
    uint8_t panels_count = sizeof(panels) / sizeof(panels[0]);
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED)
    {
       for (uint8_t i = 0; i < panels_count; i++) {
            if (clicked_btn == panels[i]) {
                ui_ConfirmKeyProcess(i);
                break;
            }
        } 
    }
}

void ui_event_ConfirmBtnBack( lv_event_t * e) {
    ScreenConfirm.deinit();
    ScreenMain.reinit();
    _ui_screen_change( &ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenMain_screen_init);
}

void ui_event_ConfirmSysReset( lv_event_t * e) {
    system("reboot");
}

void ui_event_ConfirmAppReset(lv_event_t * e) {
    execl("/honoka/lvgl_demo", "lvgl_demo", (char *)NULL);
    LOG_E(TAG, "Reset failed\r\n");
}

static void ui_UpdateLabel(void) {
    char display_key[14] = {0}; // 用于显示的字符串
    int j = 0;
    for (int i = 0; i < key_len; ++i, j += 2) {
        display_key[j] = key[i];
        if (i < key_len - 1) {
            display_key[j + 1] = ' '; // 在字符之间插入空格
        }
    }
    lv_label_set_text(ui_ConfirmLabelInput, display_key);
}

static void ui_ClearKey(void) {
    key_len = 0;
    key[0] = '\0'; // 清空字符串
    ui_UpdateLabel();
}

static void ui_AddKey(char num) {
    if (key_len < 6) { // 最大长度检查
        key[key_len++] = num;
        key[key_len] = '\0'; // 确保字符串结束
        ui_UpdateLabel();
    }
}