#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <alsa/asoundlib.h>
/************************************
宏定义
************************************/
#define PCM_PLAYBACK_DEV "hw:0,0"
/************************************
WAV 音频文件解析相关数据结构申明
************************************/
typedef struct WAV_RIFF 
{
    char ChunkID[4]; /* "RIFF" */
    u_int32_t ChunkSize; /* 从下一个地址开始到文件末尾的总字节数 */
    char Format[4]; /* "WAVE" */
} __attribute__ ((packed)) RIFF_t;
typedef struct WAV_FMT 
{
    char Subchunk1ID[4]; /* "fmt " */
    u_int32_t Subchunk1Size; /* 16 for PCM */
    u_int16_t AudioFormat; /* PCM = 1*/
    u_int16_t NumChannels; /* Mono = 1, Stereo = 2, etc. */
    u_int32_t SampleRate; /* 8000, 44100, etc. */
    u_int32_t ByteRate; /* = SampleRate * NumChannels * BitsPerSample/8 */
    u_int16_t BlockAlign; /* = NumChannels * BitsPerSample/8 */
    u_int16_t BitsPerSample; /* 8bits, 16bits, etc. */
} __attribute__ ((packed)) FMT_t;
static FMT_t wav_fmt;
typedef struct WAV_DATA 
{
    char Subchunk2ID[4]; /* "data" */
    u_int32_t Subchunk2Size; /* data size */
} __attribute__ ((packed)) DATA_t;
/************************************
static 静态全局变量定义
************************************/
static snd_pcm_t *pcm = NULL; //pcm 句柄
static unsigned int buf_bytes; //应用程序缓冲区的大小（字节为单位）
static void *buf = NULL; //指向应用程序缓冲区的指针
static int fd = -1; //指向 WAV 音频文件的文件描述符
static snd_pcm_uframes_t period_size = 1024; //周期大小（单位: 帧）
static unsigned int periods = 16; //周期数（设备驱动层 buffer 的大小）
static int snd_pcm_init(void) 
{
    snd_pcm_hw_params_t *hwparams = NULL;
    int ret;
    /* 打开 PCM 设备 */
    ret = snd_pcm_open(&pcm, PCM_PLAYBACK_DEV, SND_PCM_STREAM_PLAYBACK, 0);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_open error: %s: %s\n",
        PCM_PLAYBACK_DEV, snd_strerror(ret));
        return -1;
    }
    /* 实例化 hwparams 对象 */
    snd_pcm_hw_params_malloc(&hwparams);
    /* 获取 PCM 设备当前硬件配置,对 hwparams 进行初始化 */
    ret = snd_pcm_hw_params_any(pcm, hwparams);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_any error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /************** 
    设置参数
    ***************/
    /* 设置访问类型: 交错模式 */
    ret = snd_pcm_hw_params_set_access(pcm, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_access error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置数据格式: 有符号 16 位、小端模式 */
    ret = snd_pcm_hw_params_set_format(pcm, hwparams, SND_PCM_FORMAT_S16_LE);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_format error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置采样率 */
    ret = snd_pcm_hw_params_set_rate(pcm, hwparams, wav_fmt.SampleRate, 0);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_rate error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置声道数: 双声道 */
    ret = snd_pcm_hw_params_set_channels(pcm, hwparams, wav_fmt.NumChannels);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_channels error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置周期大小: period_size */
    ret = snd_pcm_hw_params_set_period_size(pcm, hwparams, period_size, 0);
    if (0 > ret)    
    {
        fprintf(stderr, "snd_pcm_hw_params_set_period_size error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置周期数（驱动层 buffer 的大小）: periods */
    ret = snd_pcm_hw_params_set_periods(pcm, hwparams, periods, 0);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_periods error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 使配置生效 */
    ret = snd_pcm_hw_params(pcm, hwparams);
    snd_pcm_hw_params_free(hwparams); //释放 hwparams 对象占用的内存
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params error: %s\n", snd_strerror(ret));
        goto err1;
    }
    buf_bytes = period_size * wav_fmt.BlockAlign; //变量赋值，一个周期的字节大小
    return 0;
    err2:
        snd_pcm_hw_params_free(hwparams); //释放内存
    err1:
        snd_pcm_close(pcm); //关闭 pcm 设备



    return -1; 
}
static int open_wav_file(const char *file) 
{
    RIFF_t wav_riff;
    DATA_t wav_data;
    int ret;
    fd = open(file, O_RDONLY);
    if (0 > fd) 
    {
        fprintf(stderr, "open error: %s: %s\n", file, strerror(errno));
        return -1;
    }
    /* 读取 RIFF chunk */
    ret = read(fd, &wav_riff, sizeof(RIFF_t));
    if (sizeof(RIFF_t) != ret) 
    {
        if (0 > ret)
            perror("read error");
        else
            fprintf(stderr, "check error: %s\n", file);
        close(fd);
        return -1;
    }
    if (strncmp("RIFF", wav_riff.ChunkID, 4) || strncmp("WAVE", wav_riff.Format, 4)) 
    {
        fprintf(stderr, "check error: %s\n", file);
        close(fd);
        return -1;
    }
    /* 读取 sub-chunk-fmt */
    ret = read(fd, &wav_fmt, sizeof(FMT_t));
    if (sizeof(FMT_t) != ret) 
    {
        if (0 > ret)
            perror("read error");
        else
            fprintf(stderr, "check error: %s\n", file);
        close(fd);
        return -1;
    }
    if (strncmp("fmt ", wav_fmt.Subchunk1ID, 4)) 
    {//校验
        fprintf(stderr, "check error: %s\n", file);
        close(fd);
        return -1;
    }
    /* 打印音频文件的信息 */
    printf("<<<<音频文件格式信息>>>>\n\n");
    printf(" file name: %s\n", file);
    printf(" Subchunk1Size: %u\n", wav_fmt.Subchunk1Size);
    printf(" AudioFormat: %u\n", wav_fmt.AudioFormat);
    printf(" NumChannels: %u\n", wav_fmt.NumChannels);
    printf(" SampleRate: %u\n", wav_fmt.SampleRate);
    printf(" ByteRate: %u\n", wav_fmt.ByteRate);
    printf(" BlockAlign: %u\n", wav_fmt.BlockAlign);
    printf(" BitsPerSample: %u\n\n", wav_fmt.BitsPerSample);
    /* sub-chunk-data */
    if (0 > lseek(fd, sizeof(RIFF_t) + 8 + wav_fmt.Subchunk1Size,SEEK_SET)) 
    {
        perror("lseek error");
        close(fd);
        return -1;
    }
    while(sizeof(DATA_t) == read(fd, &wav_data, sizeof(DATA_t))) 
    {
        /* 找到 sub-chunk-data */
        if (!strncmp("data", wav_data.Subchunk2ID, 4))//校验
            return 0;
        if (0 > lseek(fd, wav_data.Subchunk2Size, SEEK_CUR)) 
        {
            perror("lseek error");
            close(fd);
            return -1;
        }
    }
    fprintf(stderr, "check error: %s\n", file);
    return -1; 
}
/************************************
main 主函数
************************************/
int main(int argc, char *argv[])
{
    int ret;
    if (2 != argc) 
    {
        fprintf(stderr, "Usage: %s <audio_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* 打开 WAV 音频文件 */
    if (open_wav_file(argv[1]))
         exit(EXIT_FAILURE);
    /* 初始化 PCM Playback 设备 */
    if (snd_pcm_init())
        goto err1;
    /* 申请读缓冲区 */
    buf = malloc(buf_bytes);
    if (NULL == buf) 
    {
        perror("malloc error");
        goto err2;
    }
    /* 播放 */
    for ( ; ; ) 
    {
        memset(buf, 0x00, buf_bytes); //buf 清零
        ret = read(fd, buf, buf_bytes); //从音频文件中读取数据
        if (0 >= ret) // 如果读取出错或文件读取完毕
            goto err3;
        ret = snd_pcm_writei(pcm, buf, period_size);
        if (0 > ret) 
        {
            fprintf(stderr, "snd_pcm_writei error: %s\n", snd_strerror(ret));
            goto err3;
        }
        else if (ret < period_size) 
        {//实际写入的帧数小于指定的帧数
        //此时我们需要调整下音频文件的读位置
        //将读位置向后移动（往回移）(period_size-ret)*frame_bytes 个字节
        //frame_bytes 表示一帧的字节大小
            if (0 > lseek(fd, (ret-period_size) * wav_fmt.BlockAlign, SEEK_CUR)) 
            {
                perror("lseek error");
                goto err3;
            }
        }
    }
    err3:
        free(buf); //释放内存
    err2:
        snd_pcm_close(pcm); //关闭 pcm 设备
    err1:
        close(fd); //关闭打开的音频文件
    exit(EXIT_FAILURE);
}