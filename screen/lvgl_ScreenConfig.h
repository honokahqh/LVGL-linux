#ifndef __LVGL_SCREENCONFIG_H__
#define __LVGL_SCREENCONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "../generate/ui.h"
#include "../generate/ui_helpers.h"

#include "ScreenMain.h"
#include "ScreenConfirm.h"
#include "ScreenConfig.h"

#include "netlink.h"
#include "ntp.h"

#include "log.h"
#include "audio.h"

// 定义函数指针类型
typedef void (*InitFunc)(void);
typedef void (*ReinitFunc)(void);
typedef void (*DeinitFunc)(void);
typedef void (*PeriodPrcessFunc)(void);
// 界面状态结构体，包含函数指针
typedef struct {
    bool isActive;
    InitFunc init;     // 指向初始化函数的指针
    ReinitFunc reinit; // 指向第二次及以后初始化函数的指针
    DeinitFunc deinit; // 指向反初始化函数的指针
    PeriodPrcessFunc PeriodProcess;
} ScreenNode_t;
extern ScreenNode_t ScreenMain, ScreenConfirm, ScreenConfig, ScreenVoice, ScreenRoomMain,
    ScreenRoomWin, ScreenRoomRelay, ScreenMusic;

void ScreenExtraInit(void);
void ScreenPeriodProcess(void);
void update_time_label(lv_obj_t *label);

#endif // !__LVGL_SCREENCONFIG_H__