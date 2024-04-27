#include "lvgl_ScreenConfig.h"
#include "ScreenConfig.h"

#define TAG "Screen Config"

SubDevNode_t SubDevPanel[10];
// 预配置的名称数组
static const char *deviceNames[] = {
    "LoRa中控",
    "LoRa房态灯",
    "LoRa呼叫铃",
    "呼叫铃",
    "房态灯",
    "蓝牙音乐模块",
    "空调红外模块",
    "刷卡灯模块",
    "中控红外模块",
    "Undefined",
    // 根据需要添加更多名称
};

GuiConfig readConfig() {
    GuiConfig config = {100, 100, 50}; // 默认值
    FILE* file = fopen("/honoka/ui_log/gui_parameter", "r");
    if (file) {
        char line[128];
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "Light=%d", &config.light)) continue;
            if (sscanf(line, "Volume=%d", &config.volume)) continue;
            if (sscanf(line, "SaverLight=%d", &config.saverLight)) continue;
        }
        fclose(file);
    } else {
        printf("Failed to open configuration file.\n");
    }
    return config;
}

void version_to_string(uint8_t ver, char* str) {
    // 确保传入的str足够大以容纳结果字符串
    int major = ver / 100;             // 计算主版本号
    int minor = (ver / 10) % 10;       // 计算次版本号
    int patch = ver % 10;              // 计算修订号

    // 格式化字符串
    snprintf(str, 8, "v%d.%d.%d", major, minor, patch);
}

void update_panel_positions() {
    int activeIndex = 0; // 用于记录当前活动设备的索引

    for (size_t i = 0; i < SubDevNumMax; i++) {
        if (SubDevPanel[i].state != 0) { // 检查设备状态是否非0（活动状态）
            int posY = 40 + 60 * activeIndex;// 计算面板应当处于的Y位置
            lv_obj_set_y(SubDevPanel[i].panel, posY);// 更新面板的Y位置
            activeIndex++; // 只有当设备为活动状态时，我们才增加索引
        }
    }
}

void DeleteDev(SubDevNode_t *panelStruct)
{
    if(panelStruct->panel != NULL)
    {
        lv_obj_del(panelStruct->panel);
        panelStruct->panel = NULL;
    }
    else
        LOG_E(TAG, "panel %s inexistence, delete err\n", panelStruct->name);
}
void CreateNewDev(SubDevNode_t *panelStruct)
{   
    if(panelStruct->panel != NULL)
    {
        LOG_E(TAG, "panel %s already exist, create err\n", panelStruct->name);
        return;
    }
    lv_obj_t *ui_TempPanel = lv_obj_create(ui_ConfigPanelForDevList2);
    lv_obj_set_width( ui_TempPanel, 760);
    lv_obj_set_height( ui_TempPanel, 60);
    lv_obj_set_x( ui_TempPanel, 0 );
    lv_obj_set_y( ui_TempPanel, 50 );
    lv_obj_set_align( ui_TempPanel, LV_ALIGN_TOP_MID );
    lv_obj_clear_flag( ui_TempPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_TempPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TempPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_TempPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TempPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempDecoration1 = lv_obj_create(ui_TempPanel);
    lv_obj_set_width( ui_TempDecoration1, 650);
    lv_obj_set_height( ui_TempDecoration1, 1);
    lv_obj_set_x( ui_TempDecoration1, 0 );
    lv_obj_set_y( ui_TempDecoration1, 29 );
    lv_obj_set_align( ui_TempDecoration1, LV_ALIGN_CENTER );
    lv_obj_clear_flag( ui_TempDecoration1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(ui_TempDecoration1, lv_color_hex(0x989898), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_TempDecoration1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_TempDecoration1, lv_color_hex(0x191713), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_grad_dir(ui_TempDecoration1, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TempDecoration1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempBtnManage = lv_btn_create(ui_TempPanel);
    lv_obj_set_width( ui_TempBtnManage, 70);
    lv_obj_set_height( ui_TempBtnManage, 60);
    lv_obj_set_x( ui_TempBtnManage, 580 );
    lv_obj_set_y( ui_TempBtnManage, -25 );
    lv_obj_add_flag( ui_TempBtnManage, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
    lv_obj_clear_flag( ui_TempBtnManage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(ui_TempBtnManage, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_TempBtnManage, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempLabelManage = lv_label_create(ui_TempBtnManage);
    lv_obj_set_width( ui_TempLabelManage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_TempLabelManage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align( ui_TempLabelManage, LV_ALIGN_CENTER );
    lv_label_set_text(ui_TempLabelManage,"管理");
    lv_obj_set_style_text_color(ui_TempLabelManage, lv_color_hex(0xFFF400), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(ui_TempLabelManage, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempLabelManage, &ui_font_CN20, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempBtnUpdate = lv_btn_create(ui_TempPanel);
    lv_obj_set_width( ui_TempBtnUpdate, 70);
    lv_obj_set_height( ui_TempBtnUpdate, 60);
    lv_obj_set_x( ui_TempBtnUpdate, 500 );
    lv_obj_set_y( ui_TempBtnUpdate, -25 );
    lv_obj_add_flag( ui_TempBtnUpdate, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
    lv_obj_clear_flag( ui_TempBtnUpdate, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_bg_color(ui_TempBtnUpdate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_TempBtnUpdate, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempLabelUpdate = lv_label_create(ui_TempBtnUpdate);
    lv_obj_set_width( ui_TempLabelUpdate, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_TempLabelUpdate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align( ui_TempLabelUpdate, LV_ALIGN_CENTER );
    lv_label_set_text(ui_TempLabelUpdate,"升级");
    lv_obj_set_style_text_color(ui_TempLabelUpdate, lv_color_hex(0x2CFF2B), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_text_opa(ui_TempLabelUpdate, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempLabelUpdate, &ui_font_CN20, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempLabelDev1Name = lv_label_create(ui_TempPanel);
    lv_obj_set_width( ui_TempLabelDev1Name, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_TempLabelDev1Name, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_TempLabelDev1Name, 50 );
    lv_obj_set_y( ui_TempLabelDev1Name, -5 );
    lv_obj_set_align( ui_TempLabelDev1Name, LV_ALIGN_LEFT_MID );
    lv_label_set_text(ui_TempLabelDev1Name, panelStruct->name);
    lv_obj_set_style_text_font(ui_TempLabelDev1Name, &ui_font_CN20, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempLabelDev1State = lv_label_create(ui_TempPanel);
    lv_obj_set_width( ui_TempLabelDev1State, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_TempLabelDev1State, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_TempLabelDev1State, 220 );
    lv_obj_set_y( ui_TempLabelDev1State, -5 );
    lv_obj_set_align( ui_TempLabelDev1State, LV_ALIGN_LEFT_MID );
    if(panelStruct->state == 1)
        lv_label_set_text(ui_TempLabelDev1State,"在线");
    else
        lv_label_set_text(ui_TempLabelDev1State,"离线");
    lv_obj_set_style_text_font(ui_TempLabelDev1State, &ui_font_CN20, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_t *ui_TempLabelDev1Ver = lv_label_create(ui_TempPanel);
    lv_obj_set_width( ui_TempLabelDev1Ver, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_TempLabelDev1Ver, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_TempLabelDev1Ver, 350 );
    lv_obj_set_y( ui_TempLabelDev1Ver, -5 );
    lv_obj_set_align( ui_TempLabelDev1Ver, LV_ALIGN_LEFT_MID );
    lv_label_set_text(ui_TempLabelDev1Ver,panelStruct->ver);
    lv_obj_set_style_text_font(ui_TempLabelDev1Ver, &ui_font_CN20, LV_PART_MAIN| LV_STATE_DEFAULT);

    panelStruct->panel = ui_TempPanel;
    panelStruct->Decoration = ui_TempBtnManage;
    panelStruct->LabelManage = ui_TempLabelManage;
    panelStruct->BtnUpdate = ui_TempBtnUpdate;
    panelStruct->LabelUpdate = ui_TempLabelUpdate;
    panelStruct->LabelName = ui_TempLabelDev1Name;
    panelStruct->LabelState = ui_TempLabelDev1State;
    panelStruct->LabelVer = ui_TempLabelDev1Ver;

    // ui_ConfigLabelNoSubDev = lv_label_create(ui_ConfigPanelForDevList1);
    // lv_obj_set_width( ui_ConfigLabelNoSubDev, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height( ui_ConfigLabelNoSubDev, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_align( ui_ConfigLabelNoSubDev, LV_ALIGN_CENTER );
    // lv_label_set_text(ui_ConfigLabelNoSubDev,"未发现外接模块设备!");
    // lv_obj_set_style_text_color(ui_ConfigLabelNoSubDev, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    // lv_obj_set_style_text_opa(ui_ConfigLabelNoSubDev, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui_ConfigLabelNoSubDev, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);
}
// 初始化函数
static void ScreenInit() {

    for(uint8_t i = 0;i < SubDevNumMax;i++)
    {
        memcpy(SubDevPanel[i].name, deviceNames[i], strlen(deviceNames[i]) + 1);
        SubDevPanel[i].state = 2;
        SubDevPanel[i].version = 100 + i;
        version_to_string(SubDevPanel[i].version, SubDevPanel[i].ver);
    }

    char buffer[20];
    GuiConfig config = readConfig();
    lv_slider_set_value(ui_ConfigSliderLight, config.light, LV_ANIM_OFF);
    lv_slider_set_value(ui_ConfigSliderVoice, config.volume, LV_ANIM_OFF);
    lv_slider_set_value(ui_ConfigSliderSaverLight, config.saverLight, LV_ANIM_OFF);

    // 更新标签文本
    sprintf(buffer, "%d%%", config.light);
    lv_label_set_text(ui_ConfigLabelLight2, buffer);
    sprintf(buffer, "%d%%", config.volume);
    lv_label_set_text(ui_ConfigLabelVoice2, buffer);
    sprintf(buffer, "%d%%", config.saverLight);
    lv_label_set_text(ui_ConfigLabelSaverLight2, buffer);

    // 扩大滑条判定
    lv_obj_set_ext_click_area(ui_ConfigSliderLight, 20);
    lv_obj_set_ext_click_area(ui_ConfigSliderVoice, 20);
    lv_obj_set_ext_click_area(ui_ConfigSliderSaverLight, 20);
    lv_obj_set_ext_click_area(ui_ConfigCheckNoDHCP, 40);
    lv_obj_set_ext_click_area(ui_ConfigCheckDHCP, 40);

    lv_obj_add_event_cb(ui_ConfigPanelSetting1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelRegister1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelSubDev1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelNet1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelVersion1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelAbout1, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigBtnSubDev, ui_event_ConfigPanelChange, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigBtnBack, ui_event_ConfigBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelVoiceSet, ui_event_ConfigPanelVoiceSet, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigPanelWired, ui_event_ConfigSetNetPara, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelWLAN, ui_event_ConfigSetNetPara, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigCheckNoDHCP, ui_event_ConfigDHCP, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigCheckDHCP, ui_event_ConfigDHCP, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigSliderLight, ui_event_ConfigSlider, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_ConfigSliderSaverLight, ui_event_ConfigSlider, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_ConfigSliderVoice, ui_event_ConfigSlider, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_add_event_cb(ui_ConfigSwNetEnable, ui_event_ConfigNetEnable, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigBtnReset, ui_event_ConfigReset, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigSwEnableDebug, ui_event_ConfigDebug, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_ConfigPanelDebug, ui_event_ConfigDebug, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_ConfigDebugTextarea, ui_event_ConfigDebugTextarea, LV_EVENT_ALL, NULL);

}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit.. \n");
    ScreenConfig.isActive = true;
    ui_ConfigListSet(0);    
    for(uint8_t i = 0;i < SubDevNumMax;i++)
    {
        CreateNewDev(&SubDevPanel[i]);
    }
    update_time_label(ui_ConfigLabelTime);
    lv_obj_add_flag(ui_ConfigPanelIP, LV_OBJ_FLAG_HIDDEN);
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit.. \n");
    ScreenConfig.isActive = false;
    for(uint8_t i = 0;i < SubDevNumMax;i++)
    {
        DeleteDev(&SubDevPanel[i]);
    }
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms = 0;
    if(count_100ms % 10 == 0)
    {
        update_panel_positions();
        update_time_label(ui_ConfigLabelTime);
    }
        
    count_100ms++;
}   

ScreenNode_t ScreenConfig = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_ConfigListSet(uint8_t index)
{
    lv_obj_t * panels[] = {ui_ConfigPanelForSetting, ui_ConfigPanelForRegister, ui_ConfigPanelForSubDev, 
                           ui_ConfigPanelForNet, ui_ConfigPanelForVersion, ui_ConfigPanelForAbout, ui_ConfigPanelForDevList1};
    lv_obj_t * panels2[] = {ui_ConfigPanelSetting2, ui_ConfigPanelRegister2, ui_ConfigPanelSubDev2,
                         ui_ConfigPanelNet2, ui_ConfigPanelVersion2, ui_ConfigPanelAbout2};       
    lv_obj_t * panels3[] = {ui_ConfigLabelSetting, ui_ConfigLabelRegister, ui_ConfigLabelSubDev,
                            ui_ConfigLabelNet, ui_ConfigLabelVersion, ui_ConfigLabelAbout};     
    if(index < 6)
    {   // 前六个panel由左侧list触发,触发后左侧list要更改颜色
        for (int i = 0; i < 6; i++) {
            if (index == i) {
                lv_obj_set_style_bg_grad_color(panels2[i], lv_color_hex(0xF7BF6F), LV_PART_MAIN | LV_STATE_DEFAULT );
                lv_obj_set_style_text_color(panels3[i], lv_color_hex(0xF8D9A7), LV_PART_MAIN | LV_STATE_DEFAULT );
            } else {
                lv_obj_set_style_bg_grad_color(panels2[i], lv_color_hex(0x201E1C), LV_PART_MAIN | LV_STATE_DEFAULT );
                lv_obj_set_style_text_color(panels3[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
            }
        }
    }      
    for(int i = 0;i < sizeof(panels) / sizeof(panels[0]);i++)
    {
        if(index == i)
            lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_HIDDEN); // 显示当前面板
        else
            lv_obj_add_flag(panels[i], LV_OBJ_FLAG_HIDDEN); // 隐藏其他面板
    }
}   

void ui_event_ConfigPanelChange( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * clicked_panel = lv_event_get_target(e);
    lv_obj_t * panels[] = {ui_ConfigPanelSetting1, ui_ConfigPanelRegister1, ui_ConfigPanelSubDev1,
                         ui_ConfigPanelNet1, ui_ConfigPanelVersion1, ui_ConfigPanelAbout1,
                         ui_ConfigBtnSubDev};
    if ( event_code == LV_EVENT_CLICKED) {
        for(int i = 0;i < sizeof(panels) / sizeof(panels[0]); i++)
        {
            if(clicked_panel == panels[i])
                ui_ConfigListSet(i);
        }
    }
}

void ui_event_ConfigBtnBack( lv_event_t * e) {
    ScreenConfig.deinit();
    ScreenMain.reinit();
    _ui_screen_change( &ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenMain_screen_init);
}

void ui_event_ConfigPanelVoiceSet( lv_event_t * e) {
    ScreenConfig.deinit();
    ScreenVoice.reinit();
    _ui_screen_change( &ui_ScreenVoiceSet, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_ScreenVoiceSet_screen_init);
}

void ui_event_ConfigSetNetPara( lv_event_t * e) {
    // 检查ui_ConfigPanelIP是否已经被隐藏
    if(lv_obj_has_flag(ui_ConfigPanelIP, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(ui_ConfigPanelIP, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(ui_ConfigPanelIP, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_ConfigDHCP( lv_event_t * e) {
    lv_obj_t * clicked_panel = lv_event_get_target(e);
    // 当点击的是非DHCP配置复选框
    if(clicked_panel == ui_ConfigCheckNoDHCP) {
        // 如果非DHCP复选框被选中，则取消选中DHCP复选框
        if(lv_obj_has_state(clicked_panel, LV_STATE_CHECKED)) {
            lv_obj_clear_state(ui_ConfigCheckDHCP, LV_STATE_CHECKED);
        } else {
            // 如果点击是为了取消选中，确保DHCP复选框被选中
            lv_obj_add_state(ui_ConfigCheckDHCP, LV_STATE_CHECKED);
        }
    }
    // 当点击的是DHCP配置复选框
    else if(clicked_panel == ui_ConfigCheckDHCP) {
        // 如果DHCP复选框被选中，则取消选中非DHCP复选框
        if(lv_obj_has_state(clicked_panel, LV_STATE_CHECKED)) {
            lv_obj_clear_state(ui_ConfigCheckNoDHCP, LV_STATE_CHECKED);
        } else {
            // 如果点击是为了取消选中，确保非DHCP复选框被选中
            lv_obj_add_state(ui_ConfigCheckNoDHCP, LV_STATE_CHECKED);
        }
    } else {
        LOG_E(TAG, "%s Undefined operation\n", __func__);
    }
}

void ui_event_ConfigSlider(lv_event_t * e) {
    lv_obj_t * sliders[] = {ui_ConfigSliderLight, ui_ConfigSliderVoice, ui_ConfigSliderSaverLight};
    lv_obj_t * labels[] = {ui_ConfigLabelLight2, ui_ConfigLabelVoice2, ui_ConfigLabelSaverLight2};
    
    lv_obj_t * slider = lv_event_get_target(e);

    int value = lv_slider_get_value(slider); // 获取滑块的当前值
    char buffer[10]; // 用于存放格式化后的字符串，足够存放"100%"和终结字符'\0'
    sprintf(buffer, "%d%%", value); // 将值转换为百分比格式
    for(uint8_t i = 0; i < sizeof(sliders)/sizeof(sliders[0]); i++)
    {
        if(slider == sliders[i])
            lv_label_set_text(labels[i], buffer); // 设置标签的文本
    }
}

void ui_event_ConfigNetEnable(lv_event_t * e) {
    lv_obj_t * sw = lv_event_get_target(e);
    int ret;

    if (lv_obj_has_state(sw, LV_STATE_CHECKED)) {
        LOG_I(TAG, "ifconfig eth0 up\n");
        ret = system("ifconfig eth0 up");
    } else {
        LOG_I(TAG, "ifconfig eth0 down\n");
        ret = system("ifconfig eth0 down");
    }

    if (ret != 0) {
        // 错误处理
        LOG_E(TAG, "Failed to execute ifconfig command.\n");
    }   
}

void ui_event_ConfigReset(lv_event_t * e)
{
    system("reboot");
}

void ui_event_ConfigDebug(lv_event_t * e)
{
    lv_obj_t * clicked_panel = lv_event_get_target(e);
    // 当点击的是打开debug
    if(clicked_panel == ui_ConfigSwEnableDebug) {
        if(lv_obj_has_state(clicked_panel, LV_STATE_CHECKED)) {
            lv_obj_clear_flag(ui_ConfigPanelDebug, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(ui_ConfigPanelDebug, LV_OBJ_FLAG_HIDDEN);
        }
    } else if (clicked_panel == ui_ConfigPanelDebug) {
        if (lv_obj_has_flag(ui_ConfigKeyboard, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(ui_ConfigKeyboard, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_y(ui_ConfigDebugTextarea, 200);
        }
        else {
            lv_obj_add_flag(ui_ConfigKeyboard, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_y(ui_ConfigDebugTextarea, 420);
        }
    }
}

void ui_event_ConfigDebugTextarea(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e); // 获取事件目标，即textarea控件

    if (code == LV_EVENT_READY) {
        // 当按下回车键（通常由与textarea关联的键盘触发）
        const char * cmd = lv_textarea_get_text(ta); // 获取textarea中的文本作为命令
        if (cmd && *cmd) { // 确保命令非空
            UpdateLabelsFromCmdOutput((char *)cmd, 15); // 使用命令更新标签，假设这个函数已定义
        }
        lv_textarea_set_text(ta, ""); // 清除textarea的当前文本
    }
    else if (code == LV_EVENT_CANCEL)
    {
        lv_textarea_set_text(ta, ""); // 清除textarea的当前文本
    }
}
