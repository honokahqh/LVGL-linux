#ifndef __SCREENCONFIRM_H__
#define __SCREENCONFIRM_H__

#include "lvgl_ScreenConfig.h"

void ui_event_ConfirmInputKey(lv_event_t * e);
void ui_event_ConfirmBtnBack( lv_event_t * e);
void ui_event_ConfirmSysReset( lv_event_t * e);
void ui_event_ConfirmAppReset( lv_event_t * e);

#endif // !__SCREENCONFIRM_H__