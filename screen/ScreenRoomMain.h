#ifndef __SCREENROOMMAIN_H__
#define __SCREENROOMMAIN_H__

#include "lvgl_ScreenConfig.h"

typedef struct
{
    uint16_t BrandID;
    uint8_t sw;
    uint8_t temp;
    uint8_t mode;
    uint8_t wind;
}RoomMainAircon_t;

enum {
    Sw = 0,
    TempUp,
    TempDown,
    Mode,
    Wind
};

enum {
    ModeAuto = 0,
    ModeCooling,
    ModeHeating,
    ModeFan,
    ModeDehumidification,
};

enum {
    WindAuto = 0,
    WindLow,
    WindMid,
    WindHigh,
};

void ui_event_RoomMainBtnBack( lv_event_t * e);
void ui_event_RoomMainPanelWindow( lv_event_t * e);
void ui_event_RoomMainPanelLight( lv_event_t * e);
void ui_event_RoomMainSwitch( lv_event_t * e);
void ui_event_RoomMainAirconConfig( lv_event_t * e);


#endif // !__SCREENVOICE_H__