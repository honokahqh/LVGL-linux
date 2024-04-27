#ifndef __AUDIO_H__
#define __AUDIO_H__

#define WAV_Init    "/honoka/audio/init.wav"
#define WAV_CLICK   "/honoka/audio/click.wav"
void speaker_init(void);
void audio_start(char *file_path);
void audio_volumeSet(int volume);

#endif // !__AUDIO_H__