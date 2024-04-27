#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "generate/ui.h"
#include "screen/lvgl_ScreenConfig.h"
#include <pthread.h>

#define DISP_BUF_SIZE (1024 * 600)

int main(void)
{
    lv_init();
    lv_png_init();
    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf; 
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 1024;
    disp_drv.ver_res    = 600;
    lv_disp_drv_register(&disp_drv);

    /* Linux input device init */
    evdev_init();
    /* Initialize and register a display input driver */
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/

    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv); 

    /*Create a Demo*/
    ui_init();
    ScreenExtraInit();
    
    /* netlink task */
    pthread_t tid;
	pthread_create(&tid, NULL, net_link_thread, NULL);
    /* netlink task */
    pthread_t ntpId;
	pthread_create(&ntpId, NULL, syn_ntp_time, NULL);
    /*Handle LVGL tasks*/
    while(1) {
        lv_timer_handler();
        ScreenPeriodProcess();
        usleep(1000); // 时间片配置为200Hz,usleep时间不重要,最低也要5ms
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void) {
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (uint64_t)tv_start.tv_sec * 1000LL + (tv_start.tv_usec / 1000);
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms = (uint64_t)tv_now.tv_sec * 1000LL + (tv_now.tv_usec / 1000);

    // 由于返回类型是uint32_t，所以这里的结果会自动回绕
    uint32_t time_ms = (uint32_t)(now_ms - start_ms);
    return time_ms;
}
