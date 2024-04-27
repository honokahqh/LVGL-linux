#ifndef __SCREENCONFIG_H__
#define __SCREENCONFIG_H__

#include "lvgl_ScreenConfig.h"

#define SubDevNameMax      20
#define SubDevNumMax       10
// 中控 呼叫铃 房态灯 红外 蓝牙 
typedef struct
{
    uint8_t state;
    uint16_t id;
    uint16_t version;
    char name[SubDevNameMax];
    char ver[10];
    lv_obj_t *panel;
    lv_obj_t *LabelName;
    lv_obj_t *LabelState;
    lv_obj_t *LabelVer;
    lv_obj_t *BtnUpdate;
    lv_obj_t *LabelUpdate;
    lv_obj_t *BtnManage;
    lv_obj_t *LabelManage;
    lv_obj_t *Decoration;
}SubDevNode_t;
extern SubDevNode_t SubDevPanel[10];

typedef struct
{
    uint8_t ip_addr[4];
    uint8_t ip_mask[4];
    uint8_t gatewayip[4];
    uint8_t MainDNS[4];
    uint8_t SubDNS[4];    
    uint8_t isDHCP;
}IP_State_t;

typedef struct {
    int light;
    int volume;
    int saverLight;
} GuiConfig;


void ui_event_ConfigPanelChange( lv_event_t * e);
void ui_event_ConfigBtnBack( lv_event_t * e);
void ui_event_ConfigPanelVoiceSet( lv_event_t * e);
void ui_event_ConfigSetNetPara( lv_event_t * e);
void ui_event_ConfigDHCP( lv_event_t * e);
void ui_event_ConfigSlider(lv_event_t * e);
void ui_event_ConfigNetEnable(lv_event_t * e);
void ui_event_ConfigReset(lv_event_t * e);
void ui_event_ConfigReset(lv_event_t * e);
void ui_event_ConfigDebug(lv_event_t * e);
void ui_event_ConfigDebugTextarea(lv_event_t * e);


void UpdateLabelsFromCmdOutput(char *cmd, int labelNum);

#endif // !__SCREENCONFIG_H__