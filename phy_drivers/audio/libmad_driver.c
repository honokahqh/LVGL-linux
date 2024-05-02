#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include "mad.h"
#include "libmad_driver.h"

#define BUFSIZE 8192

/*
 * 私有消息结构体。这个结构体的通用指针被传递给每个回调函数。
 * 可以在此结构体中存放任何你需要在回调中访问的数据。
 */
typedef struct {
    FILE *file_ptr;        // 文件指针
    unsigned int file_len; // 文件长度
    unsigned int file_pos; // 当前位置
    unsigned char file_buf[BUFSIZE]; // 缓冲区
    unsigned int buf_size;  // 缓冲区的实际大小
    struct mad_decoder decoder;
    int (*output_handler)(void *data, int length, int frq, int channels);
}mp3_file;
mp3_file mp3_data;

static enum mad_flow input(void *data, struct mad_stream *stream) {
    mp3_file *mp3_data;
    int return_code;
    int unprocessed_data_size; // 未处理数据的大小
    int copy_size;

    mp3_data = (mp3_file *)data;
    if (mp3_data->file_pos < mp3_data->file_len) {
        unprocessed_data_size = stream->bufend - stream->next_frame;
        memcpy(mp3_data->file_buf, mp3_data->file_buf + mp3_data->buf_size - unprocessed_data_size, unprocessed_data_size);
        copy_size = BUFSIZE - unprocessed_data_size;
        if (mp3_data->file_pos + copy_size > mp3_data->file_len) {
            copy_size = mp3_data->file_len - mp3_data->file_pos;
        }
        fread(mp3_data->file_buf + unprocessed_data_size, 1, copy_size, mp3_data->file_ptr);
        mp3_data->buf_size = unprocessed_data_size + copy_size;
        mp3_data->file_pos += copy_size;

        // 将缓冲区的数据提供给mp3输入流
        mad_stream_buffer(stream, mp3_data->file_buf, mp3_data->buf_size);
        return_code = MAD_FLOW_CONTINUE;
    } else {
        return_code = MAD_FLOW_STOP;
    }

    return return_code;
}

/*
 * The following utility routine performs simple rounding, clipping, and
 * scaling of MAD's high-resolution samples down to 16 bits. It does not
 * perform any dithering or noise shaping, which would be recommended to
 * obtain any exceptional audio quality. It is therefore not recommended to
 * use this routine if high-quality output is desired.
 */

static inline signed int scale(mad_fixed_t sample)
{
    /* round */
    sample += (1L << (MAD_F_FRACBITS - 16));

    /* clip */
    if (sample >= MAD_F_ONE)
        sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
        sample = -MAD_F_ONE;

    /* quantize */
    return sample >> (MAD_F_FRACBITS + 1 - 16);
}

/*
 * This is the output callback function. It is called after each frame of
 * MPEG audio data has been completely decoded. The purpose of this callback
 * is to output (or play) the decoded PCM audio.
 */

static enum mad_flow output(void *data, struct mad_header const *header,
        struct mad_pcm *pcm)
{
    unsigned int nchannels, nsamples;
    mad_fixed_t const *left_ch, *right_ch;
    static int first_call = 1;
    int return_code;
    if (first_call) {
        printf("frquence: %u Hz\n", header->samplerate);
        first_call = 0;
    }
    // pcm->samplerate contains the sampling frequency
    nchannels = pcm->channels;
    nsamples = pcm->length;
    left_ch = pcm->samples[0];
    right_ch = pcm->samples[1];
    short buf[nsamples *2];
    int i = 0;
    //printf(">>%d\n", nsamples);
    while (nsamples--) {
        signed int sample;
        // output sample(s) in 16-bit signed little-endian PCM
        sample = scale(*left_ch++);
        buf[i++] = sample & 0xFFFF;
        if (nchannels == 2) {
            sample = scale(*right_ch++);
            buf[i++] = sample & 0xFFFF;
        }
    }
    if(mp3_data.output_handler != NULL)
        return_code = mp3_data.output_handler(buf, i, header->samplerate, nchannels);
    if(return_code == -1)
        return MAD_FLOW_STOP;
    return MAD_FLOW_CONTINUE;
}

/*
 * This is the error callback function. It is called whenever a decoding
 * error occurs.     The error is indicated by stream->error; the list of
 * possible MAD_ERROR_* errors can be found in the mad.h (or stream.h)
 * header file.
 */

static enum mad_flow error(void *data,
        struct mad_stream *stream,
        struct mad_frame *frame)
{
    mp3_file *mp3fp = data;

    fprintf(stderr, "decoding error 0x%04x (%s) at byte offset %u\n",
            stream->error, mad_stream_errorstr(stream),
            stream->this_frame - mp3fp->file_buf);

    /* return MAD_FLOW_BREAK here to stop decoding (and propagate an error) */
    
    return MAD_FLOW_CONTINUE;
}

int Initialize_MP3Decoder(const char *new_filename, void *outputHandler) {
    // 关闭当前打开的文件和声卡设备
    if (mp3_data.file_ptr != NULL) {
        fclose(mp3_data.file_ptr);
        mp3_data.file_ptr = NULL;
    }

    // 重新打开新的MP3文件
    mp3_data.file_ptr = fopen(new_filename, "r");
    if (mp3_data.file_ptr == NULL) {
        fprintf(stderr, "Failed to open new MP3 file: %s\n", new_filename);
        return -1;
    }

    // 获取文件长度
    long file_start = ftell(mp3_data.file_ptr); 
    fseek(mp3_data.file_ptr, 0, SEEK_END);      
    long file_end = ftell(mp3_data.file_ptr); 
    mp3_data.file_len = file_end - file_start;
    fseek(mp3_data.file_ptr, 0, SEEK_SET); // 重新指向文件起始
    printf("file size:%d \n", mp3_data.file_len);
    mp3_data.output_handler = outputHandler;

    // 重新初始化解码器
    mad_decoder_finish(&mp3_data.decoder);  // 确保解码器结束
    mad_decoder_init(&mp3_data.decoder, &mp3_data, input, 0, 0, output, error, 0);
    mad_decoder_run(&mp3_data.decoder, MAD_DECODER_MODE_SYNC);  // 重新启动解码过程
    mad_decoder_finish(&mp3_data.decoder);

    return 1;
}