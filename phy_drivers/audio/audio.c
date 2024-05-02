/*  !!!没开线程锁,需要保证顺序执行!!!   */
#include "audio.h"
#include "libmad_driver.h"

#define TAG "audio driver"

#define WAV_HEADER_SIZE 44
#define SAMPLE_PER_FRAME 2304
#define MAX_FRAMES      20
#define AO_DEV_LINE_OUT         (0)
#define AO_DEV_I2S_TX           (1)

typedef struct {
    MI_AUDIO_DEV aoDevId;
    MI_AO_CHN aoChn;
    char *FilePath;
    volatile int hasNewAudio; // 1:有新的音频需要播放
    volatile int mp3PlayState; // 0:停止 1:播放 2:暂停
} AudioThreadaudio;
AudioThreadaudio audio;

typedef struct{
    short buf[SAMPLE_PER_FRAME];
    int length;
    int frq;
    int channels;
}mp3Frame_t;

typedef struct{
    mp3Frame_t frame[MAX_FRAMES];
    uint8_t Head;
    uint8_t Tail;
    uint8_t Num;    
    uint8_t hasNewMP3;
    uint8_t playState;
    char *FilePath;
}AudioMP3State_t;
AudioMP3State_t AudioMP3State;

static void mp3Decoder();
static int mp3_frameDataProcess(uint16_t *data, int length, int frq, int channels);
static int mp3_frameDataRead(uint8_t *data, int *length, int *frq, int *channels);

void* audioPlayThread(void *arg) {
    AudioThreadaudio *audio = (AudioThreadaudio *)arg;
    MI_AUDIO_Frame_t frame;
    frame.apVirAddr[0] = malloc(SAMPLE_PER_FRAME * 2);
    int errCount;
    int fd = -1; // 初始化 fd 为无效值
    int lastsampleRate = E_MI_AUDIO_SAMPLE_RATE_44100, sampleRate = E_MI_AUDIO_SAMPLE_RATE_44100;
    int lastchannel = 2, channels = 2;

    while (1) {
        if (audio->hasNewAudio) {
            audio->hasNewAudio = 0;  // 重置标志位
            if (fd > 0) // 上一次音频播放还未结束,被打断
            close(fd);
            fd = open(audio->FilePath, O_RDONLY);
            if (fd < 0) {
                LOG_E(TAG, "Failed to open audio file");
                continue; // 跳过当前迭代
            }
            lseek(fd, WAV_HEADER_SIZE, SEEK_SET);
        }
        if (fd >= 0) { // 检查 fd 是否有效
            frame.u32Len = SAMPLE_PER_FRAME;
            ssize_t bytesRead;

            if ((bytesRead = read(fd, frame.apVirAddr[0], frame.u32Len)) > 0) {
                frame.u32Len = bytesRead;
                errCount = 0;
                while (MI_AO_SendFrame(audio->aoDevId, audio->aoChn, &frame, 0) != MI_SUCCESS) {
                    usleep(1000 * 10); 
                    errCount++;
                    if(errCount > 10)
                        break;
                }
                if(errCount > 10) {
                    LOG_E(TAG, "MI_AO_SendFrame failed\n");
                    // 处理错误，如重置逻辑或尝试恢复
                }
            }
            else { // 文件读完,close
                close(fd);
                fd = -1;
            }
        }
        else if(AudioMP3State.playState && mp3_frameDataRead(frame.apVirAddr[0], &frame.u32Len, &sampleRate, &channels)){
            if(sampleRate != lastsampleRate || channels != lastchannel)
            {
                LOG_I(TAG, "audio parameter changed, frq:%d, channles:%d\n", sampleRate, channels);
                MI_AUDIO_Attr_t aoAttr = {
                    .eBitwidth = E_MI_AUDIO_BIT_WIDTH_16,
                    .eSamplerate = sampleRate,
                    .eSoundmode = E_MI_AUDIO_SOUND_MODE_STEREO,
                    .eWorkmode = E_MI_AUDIO_MODE_I2S_MASTER,
                    .u32ChnCnt = channels,
                    .u32PtNumPerFrm = SAMPLE_PER_FRAME
                };
                MI_AO_SetPubAttr(audio->aoDevId, &aoAttr);
                lastsampleRate = sampleRate;
                lastchannel = channels;
            }
            errCount = 0;
            while (MI_AO_SendFrame(audio->aoDevId, audio->aoChn, &frame, 0) != MI_SUCCESS) {
                usleep(1000); 
                errCount++;
                if(errCount > 10) {
                    LOG_E(TAG, "MI_AO_SendFrame failed\n");
                    // 处理错误，如重置逻辑或尝试恢复
                }
            }
        }   
        else{
            usleep(10 * 1000); // 10ms
        }
    }
    return NULL;
}

void speaker_init() {

    MI_AUDIO_Attr_t aoAttr = {
        .eBitwidth = E_MI_AUDIO_BIT_WIDTH_16,
        .eSamplerate = E_MI_AUDIO_SAMPLE_RATE_44100,
        .eSoundmode = E_MI_AUDIO_SOUND_MODE_STEREO,
        .eWorkmode = E_MI_AUDIO_MODE_I2S_MASTER,
        .u32ChnCnt = 2,
        .u32PtNumPerFrm = SAMPLE_PER_FRAME
    };
    
    audio.aoDevId = AO_DEV_LINE_OUT;
    audio.aoChn = 0;
    audio.FilePath = strdup(WAV_Init);  
    audio.hasNewAudio = 1;

    MI_SYS_Init();
    MI_AO_SetPubAttr(audio.aoDevId, &aoAttr);
    MI_AO_Enable(audio.aoDevId);
    MI_AO_EnableChn(audio.aoDevId, audio.aoChn);
    MI_AO_SetVolume(audio.aoDevId, -30);

    pthread_t threadAudio, threadMP3Decoder;
    pthread_attr_t attr;
    struct sched_param param;

    // 初始化线程属性
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

    // 设置音频线程优先级最高
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&threadAudio, &attr, audioPlayThread, &audio);

    // 设置MP3解码线程优先级稍低
    param.sched_priority -= 1; // 确保比音频线程优先级低
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&threadMP3Decoder, &attr, mp3Decoder, NULL);

    // pthread_join(threadAudio, NULL);
    // pthread_join(threadMP3Decoder, NULL);

    // pthread_attr_destroy(&attr); // 清理线程属性对象
}

void audio_start(char *file_path) {
    if (audio.FilePath != NULL) {
        free(audio.FilePath);  // 如果有，先释放旧内存
        audio.FilePath = NULL;
    }
    audio.FilePath = strdup(file_path);  // 复制并存储新路径
    audio.hasNewAudio = 1;
}

void audio_volumeSet(int volume)
{
    if(volume > 30 || volume < -60)
        return;
    MI_AO_SetVolume(audio.aoDevId, volume);
}
void mp3Decoder()
{
    memset(&AudioMP3State, 0, sizeof(AudioMP3State_t));
    while(1)
    {
        if(AudioMP3State.hasNewMP3)
        {
            AudioMP3State.hasNewMP3 = 0;
            // 清缓存
            AudioMP3State.Head = 0;
            AudioMP3State.Tail = 0;
            AudioMP3State.Num = 0; 
            AudioMP3State.playState = 1;
            Initialize_MP3Decoder(AudioMP3State.FilePath, mp3_frameDataProcess); // 函数执行完毕即解码完成
            AudioMP3State.playState = 0;
        }
        usleep(100 * 1000);
    }
}

int mp3_frameDataProcess(uint16_t *data, int length, int frq, int channels)
{
    // MP3解码默认16bit,传入音频默认8bit,长度*2
    while(AudioMP3State.Num >= MAX_FRAMES && AudioMP3State.hasNewMP3 == 0){
        usleep(20000);
    }
    if(AudioMP3State.hasNewMP3)
        return -1;
    if(length > SAMPLE_PER_FRAME)
    {
        LOG_E(TAG, "mp3 frame data length error:%d\n", length);
        return;
    }
    memcpy(AudioMP3State.frame[AudioMP3State.Tail].buf, data, length * 2);
    AudioMP3State.frame[AudioMP3State.Tail].length = length * 2;
    AudioMP3State.frame[AudioMP3State.Tail].frq = frq;
    AudioMP3State.frame[AudioMP3State.Tail].channels = channels;
    AudioMP3State.Tail = (AudioMP3State.Tail + 1) % MAX_FRAMES;
    AudioMP3State.Num++;
}

int mp3_frameDataRead(uint8_t *data, int *length, int *frq, int *channels)
{
    // LOG_I(TAG, "Frame Num:%d\n", AudioMP3State.Num);
    if(AudioMP3State.Num <= 0)
        return -1;
    memcpy(data, AudioMP3State.frame[AudioMP3State.Head].buf, AudioMP3State.frame[AudioMP3State.Head].length);
    *length = AudioMP3State.frame[AudioMP3State.Head].length;
    *frq = AudioMP3State.frame[AudioMP3State.Head].frq;
    *channels = AudioMP3State.frame[AudioMP3State.Head].channels;
    AudioMP3State.Head = (AudioMP3State.Head + 1) % MAX_FRAMES;
    AudioMP3State.Num--;
    return 1;
}

void audio_mp3Init(const char *file_path)
{
    LOG_I(TAG, "mp3 decoder init\n");
    if (AudioMP3State.FilePath != NULL) {
        free(AudioMP3State.FilePath);  // 如果有，先释放旧内存
        AudioMP3State.FilePath = NULL;
    }
    AudioMP3State.FilePath = strdup(file_path);
    AudioMP3State.hasNewMP3 = 1;
}

void audio_mp3SetPlayState(uint8_t state)
{
    AudioMP3State.playState = state;
}