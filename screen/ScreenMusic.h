#ifndef __SCREENMUSIC_H__
#define __SCREENMUSIC_H__

#include "lvgl_ScreenConfig.h"

void ui_event_MusicBtnBack( lv_event_t * e);
void ui_event_MusicChange( lv_event_t * e);
int creatPanel_from_mp3files(const char *directory_path) ;

#define MusicPanelMax 50
typedef struct 
{
    lv_obj_t *Btn[MusicPanelMax];
    lv_obj_t *Label[MusicPanelMax];
    int index;
    int Num;
    bool isPlay;
    bool isRandomLoop;
}MusicState_t;

#endif