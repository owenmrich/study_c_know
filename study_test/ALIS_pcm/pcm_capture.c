#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <alsa/asoundlib.h>
/************************************
宏定义
************************************/
#define PCM_CAPTURE_DEV "hw:0,0"
/************************************
static 静态全局变量定义
************************************/
static snd_pcm_t *pcm = NULL; //pcm 句柄
static snd_pcm_uframes_t period_size = 1024; //周期大小（单位: 帧）
static unsigned int periods = 16; //周期数（buffer 的大小）
static unsigned int rate = 44100; //采样率
static int snd_pcm_init(void) 
{
    snd_pcm_hw_params_t *hwparams = NULL;
    int ret;
    /* 打开 PCM 设备 */
    ret = snd_pcm_open(&pcm, PCM_CAPTURE_DEV, SND_PCM_STREAM_CAPTURE, 0);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_open error: %s: %s\n",
        PCM_CAPTURE_DEV, snd_strerror(ret));
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
    ret = snd_pcm_hw_params_set_rate(pcm, hwparams, rate, 0);
    if (0 > ret) 
    {
        fprintf(stderr, "snd_pcm_hw_params_set_rate error: %s\n", snd_strerror(ret));
        goto err2;
    }
    /* 设置声道数: 双声道 */
    ret = snd_pcm_hw_params_set_channels(pcm, hwparams, 2);
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
    /* 设置周期数（buffer 的大小）: periods */
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
    return 0;
    err2:
        snd_pcm_hw_params_free(hwparams); //释放内存
    err1:
        snd_pcm_close(pcm); //关闭 pcm 设备
    return -1; 
}
/************************************
main 主函数
************************************/
int main(int argc, char *argv[])
{
    unsigned char *buf = NULL;
    unsigned int buf_bytes;
    int fd = -1;
    int ret;
    if (2 != argc) 
    {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* 初始化 PCM Capture 设备 */
    if (snd_pcm_init())
        exit(EXIT_FAILURE);
    /* 申请读缓冲区 */
    buf_bytes = period_size * 4; //字节大小 = 周期大小*帧的字节大小 16 位双声道
    buf = malloc(buf_bytes);
    if (NULL == buf) 
    {
        perror("malloc error");
        goto err1;
    }
    /* 打开一个新建文件 */
    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL);
    if (0 > fd) 
    {
        fprintf(stderr, "open error: %s: %s\n", argv[1], strerror(errno));
        goto err2;
    }
    /* 录音 */
    for ( ; ; ) 
    {
        //memset(buf, 0x00, buf_bytes); //buf 清零
        ret = snd_pcm_readi(pcm, buf, period_size);//读取 PCM 数据 一个周期
        if (0 > ret) 
        {
            fprintf(stderr, "snd_pcm_readi error: %s\n", snd_strerror(ret));
            goto err3;
        }
        // snd_pcm_readi 的返回值 ret 等于实际读取的帧数 * 4 转为字节数
        ret = write(fd, buf, ret * 4); //将读取到的数据写入文件中
        if (0 >= ret)
            goto err3;
    }
    err3:
        close(fd); //关闭文件
    err2:
        free(buf); //释放内存
    err1:
        snd_pcm_close(pcm); //关闭 pcm 设备
    exit(EXIT_FAILURE);
}