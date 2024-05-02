#ifndef __AUDIO_H__
#define __AUDIO_H__

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
#include "log.h"

#define AudioResourcePath      "/honoka/audio/"
#define WAV_Init    "/honoka/audio/init.wav"
#define WAV_CLICK   "/honoka/audio/click.wav"
#define MP3_TEST    "/honoka/audio/test.mp3"

void speaker_init(void);
void audio_start(char *file_path);
void audio_volumeSet(int volume);
void audio_mp3Init(const char *file_path);
void audio_mp3SetPlayState(uint8_t state);

#endif // !__AUDIO_H__