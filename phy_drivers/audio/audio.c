#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mi_common_datatype.h"
#include "mi_sys.h"
#include "mi_ao.h"
#include "audio.h"
#include "log.h"

#define TAG "audio driver"

#define WAV_HEADER_SIZE 44
#define SAMPLE_PER_FRAME 1024

typedef struct {
    MI_AUDIO_DEV aoDevId;
    MI_AO_CHN aoChn;
    char *FilePath;
    volatile int hasNewAudio;
} AudioThreadaudio;

AudioThreadaudio audio;

static void setup_gpio(int gpio, const char *direction, int value);

void* audioPlayThread(void *arg) {
    AudioThreadaudio *audio = (AudioThreadaudio *)arg;

    while (1) {
        usleep(10000);  // 间隔一段时间检查是否有新音频
        if (audio->hasNewAudio) {
            audio->hasNewAudio = 0;
            int fd = open(audio->FilePath, O_RDONLY);
            if (fd < 0) {
                LOG_E(TAG, "Failed to open audio file");
            }
            else
            {
                lseek(fd, WAV_HEADER_SIZE, SEEK_SET);
                MI_AUDIO_Frame_t frame;
                frame.u32Len = SAMPLE_PER_FRAME;
                frame.apVirAddr[0] = malloc(SAMPLE_PER_FRAME);
                ssize_t bytesRead;

                while ((bytesRead = read(fd, frame.apVirAddr[0], frame.u32Len)) > 0 && (!audio->hasNewAudio)) {
                    if (MI_AO_SendFrame(audio->aoDevId, audio->aoChn, &frame, 0) != MI_SUCCESS) {
                        usleep(1000); 
                    }
                }

                free(frame.apVirAddr[0]);
                close(fd);
            }
        }
    }

    return NULL;
}

void speaker_init() {

    MI_AUDIO_Attr_t aoAttr = {
        .eBitwidth = E_MI_AUDIO_BIT_WIDTH_16,
        .eSamplerate = E_MI_AUDIO_SAMPLE_RATE_48000,
        .eSoundmode = E_MI_AUDIO_SOUND_MODE_STEREO,
        .eWorkmode = E_MI_AUDIO_MODE_I2S_MASTER,
        .u32ChnCnt = 2,
        .u32PtNumPerFrm = SAMPLE_PER_FRAME
    };
    
    audio.aoDevId = 0;
    audio.aoChn = 0;
    audio.FilePath = strdup(WAV_Init);  
    audio.hasNewAudio = 1;

    MI_SYS_Init();
    MI_AO_SetPubAttr(audio.aoDevId, &aoAttr);
    MI_AO_Enable(audio.aoDevId);
    MI_AO_EnableChn(audio.aoDevId, audio.aoChn);
    MI_AO_SetVolume(audio.aoDevId, 0);
    setup_gpio(14, "out", 1);

    pthread_t threadId;
    pthread_attr_t attr;
    struct sched_param param;

    // 初始化线程属性
    pthread_attr_init(&attr);

    // 设置线程继承属性为显式
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

    // 设置调度策略为先进先出
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

    // 设置线程优先级
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_attr_setschedparam(&attr, &param);

    // 创建线程
    pthread_create(&threadId, &attr, audioPlayThread, &audio);
}

void audio_start(char *file_path) {
    free(audio.FilePath);  // 释放之前的路径内存
    audio.FilePath = strdup(file_path);  // 复制并存储新路径
    audio.hasNewAudio = 1;
}

void audio_volumeSet(int volume)
{
    if(volume > 30 || volume < -60)
        return;
    MI_AO_SetVolume(audio.aoDevId, volume);
}

void setup_gpio(int gpio, const char *direction, int value) {
    int fd;
    char buf[50];

    // 检查GPIO是否已经导出
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
        // 如果未导出，则导出GPIO
        fd = open("/sys/class/gpio/export", O_WRONLY);
        if (fd == -1) {
            perror("Unable to open /sys/class/gpio/export");
            exit(1);
        }
        snprintf(buf, sizeof(buf), "%d", gpio);
        if (write(fd, buf, strlen(buf)) != strlen(buf)) {
            perror("Error writing to /sys/class/gpio/export");
            exit(1);
        }
        close(fd);
        // 需要稍微延时一下确保文件系统已更新
        usleep(100000);

        // 再次尝试打开方向文件
        snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
        fd = open(buf, O_WRONLY);
        if (fd == -1) {
            perror("Unable to open gpio direction file after export");
            exit(1);
        }
    }

    // 设置GPIO方向
    if (write(fd, direction, strlen(direction)) != strlen(direction)) {
        perror("Error writing to gpio direction file");
        exit(1);
    }
    close(fd);

    // 设置GPIO值
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open gpio value file");
        exit(1);
    }
    snprintf(buf, sizeof(buf), "%d", value);
    if (write(fd, buf, strlen(buf)) != strlen(buf)) {
        perror("Error writing to gpio value file");
        exit(1);
    }
    close(fd);
}