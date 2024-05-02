#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "ScreenMusic.h"

#define TAG "Screen Music"

MusicState_t MusicState;

int creatPanel_from_mp3files(const char *directory_path); // 创建一个新的panel用于显示音乐信息

// 初始化函数
static void ScreenInit() {
    lv_obj_add_event_cb(ui_MusicBtnBack, ui_event_MusicBtnBack, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MusicBtnStart, ui_event_MusicChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MusicBtnNext, ui_event_MusicChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MusicBtnLast, ui_event_MusicChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MusicBtnVoice, ui_event_MusicChange, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_MusicBtnMode, ui_event_MusicChange, LV_EVENT_CLICKED, NULL);
    for(int i = 0;i < MusicPanelMax;i++){
        MusicState.Btn[i] = NULL;
    }
}

// 初始化函数
static void ScreenReinit() {
    LOG_I(TAG, "reinit \n");
    MusicState.Num = 0;
    creatPanel_from_mp3files("/honoka/music/");
    update_time_label(ui_MusicLabelTime);
    if (MusicState.Btn[0] != NULL)
        lv_label_set_text(ui_MusicLabelMusicNow, lv_label_get_text(MusicState.Label[0]));
    lv_obj_set_style_bg_opa(MusicState.Btn[MusicState.index], 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_label_set_text(ui_MusicLabelMusicNow, lv_label_get_text(MusicState.Label[MusicState.index]));
    ScreenMusic.isActive = true;
}

// 反初始化函数
static void ScreenDeinit() {
    LOG_I(TAG, "deinit \n");
    for (uint8_t i = 0;i < MusicState.Num; i++) {
        if(MusicState.Btn[i] != NULL) {
            lv_obj_del(MusicState.Btn[i]);
            MusicState.Btn[i] = NULL;
        }
    }
    ScreenMusic.isActive = false;
}

// 周期处理的事件
static void PeriodProcess() {
    static uint32_t count_100ms;
    count_100ms++;
    if(count_100ms % 100 == 0)
        update_time_label(ui_MusicLabelTime);
}   

ScreenNode_t ScreenMusic = {false, ScreenInit, ScreenReinit, ScreenDeinit, PeriodProcess};

void ui_event_MusicBtnBack( lv_event_t * e) {
    ScreenMusic.deinit();
    ScreenMain.reinit();
    _ui_screen_change( &ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_ScreenMain_screen_init);
}

void ui_event_MusicChange( lv_event_t * e) {  
    lv_obj_t * btns[] = {ui_MusicBtnVoice, ui_MusicBtnLast, ui_MusicBtnNext, ui_MusicBtnStart, ui_MusicBtnMode};                 
    lv_obj_t * btn = lv_event_get_target(e);
    for(int i = 0;i < MusicState.Num; i++)
    {
        lv_obj_set_style_bg_opa(MusicState.Btn[i], 0, LV_PART_MAIN| LV_STATE_DEFAULT);
        if(btn == MusicState.Btn[i])
        {
            MusicState.index = i;
            char file_path[256];
            snprintf(file_path, sizeof(file_path), "%s%s", AudioResourcePath, lv_label_get_text(MusicState.Label[i]));
            audio_mp3Init(file_path);
            MusicState.isPlay = 1;
        }
    }
    for(int i = 0;i < sizeof(btns) / sizeof(btns[0]);i++)
    {
        if(btn == btns[i])
        {
            switch (i)
            {
            case 0: // voice
                break;
            case 1: // last
                if(MusicState.isRandomLoop) {
                    int newIndex;
                    do {
                        newIndex = rand() % MusicState.Num;
                    } while(newIndex == MusicState.index && MusicState.Num > 1);
                    MusicState.index = newIndex;
                }
                else if (MusicState.index != 0)
                    MusicState.index--;
                break;
            case 2: // next
                if(MusicState.isRandomLoop) {
                    int newIndex;
                    do {
                        newIndex = rand() % MusicState.Num;
                    } while(newIndex == MusicState.index && MusicState.Num > 1);
                    MusicState.index = newIndex;
                }
                else{
                    MusicState.index = (MusicState.index + 1) % MusicState.Num;
                }
                break;
            case 3: // play/pause
                MusicState.isPlay = (MusicState.isPlay + 1) % 2;
                break;
            case 4:
                MusicState.isRandomLoop = (MusicState.isRandomLoop + 1) % 2;
                if(MusicState.isRandomLoop)
                    lv_label_set_text(ui_MusicLabelMode,"随");
                else
                    lv_label_set_text(ui_MusicLabelMode,"列");
                break;
            default:
                break;
            }
        }
    }
    audio_mp3SetPlayState(MusicState.isPlay);
    if(!MusicState.isPlay)
    {
        lv_label_set_text(ui_MusicLabelStart,"播");
        LOG_I(TAG, "music start\n");
    }             
    else
    {
        lv_label_set_text(ui_MusicLabelStart,"停");
        LOG_I(TAG, "music pause\n");
    }
    lv_obj_set_style_bg_opa(MusicState.Btn[MusicState.index], 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_label_set_text(ui_MusicLabelMusicNow, lv_label_get_text(MusicState.Label[MusicState.index]));
}

// 定义函数，获取指定目录下的.mp3文件总数和名称
int creatPanel_from_mp3files(const char *directory_path) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    // 尝试打开目录
    dir = opendir(directory_path);
    if (dir == NULL) {
        perror("opendir failed");
        return -1; // 返回-1表示出错
    }

    // 遍历目录中的每个文件和子目录
    while ((entry = readdir(dir)) != NULL) {
        // 检查文件名是否以.mp3结尾
        if (strstr(entry->d_name, ".mp3")) {
            LOG_I(TAG, "Found: %s\n", entry->d_name); // 打印文件名
            CreatMusicPanel(entry->d_name, count);
            count++; // 增加计数器
        }
    }

    // 关闭目录
    closedir(dir);
    return count; // 返回找到的.mp3文件总数
}

void CreatMusicPanel(char *fileName, int index)
{
    MusicState.Btn[index] = lv_btn_create(ui_MusicPanelMusicList);
    lv_obj_set_width( MusicState.Btn[index], 380);
    lv_obj_set_height( MusicState.Btn[index], 70);
    lv_obj_set_x( MusicState.Btn[index], (index % 2) * 460 );
    lv_obj_set_y( MusicState.Btn[index], (index / 2) * 80 );
    lv_obj_clear_flag( MusicState.Btn[index], LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_add_flag( MusicState.Btn[index], LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
    lv_obj_set_style_bg_color(MusicState.Btn[index], lv_color_hex(0x2A2D2C), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(MusicState.Btn[index], 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    MusicState.Label[index] = lv_label_create(MusicState.Btn[index]);
    lv_obj_set_width( MusicState.Label[index], LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( MusicState.Label[index], LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align( MusicState.Label[index], LV_ALIGN_LEFT_MID );
    lv_label_set_text(MusicState.Label[index], fileName);
    lv_obj_set_style_text_font(MusicState.Label[index], &ui_font_CN28, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_obj_add_event_cb(MusicState.Btn[index], ui_event_MusicChange, LV_EVENT_CLICKED, NULL);

    MusicState.Num++;
}