对外接口
    1. speaker_init(void) 初始化音频接口,并播放init.wav
    2. audio_start(char *file_path) 播放一个wav格式的音频
    3. audio_volumeSet(int volume) 设置音频音量
    4. audio_mp3Init(void) 初始化一个MP3播放器,会自动开始播放,会被2给打断
    5. audio_mp3SetPlayState(bool state) 设置MP3播放状态