#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "MQTTClient.h" //包含 MQTT 客户端库头文件
/* ########################宏定义##################### */
#define BROKER_ADDRESS "tcp://iot.ranye-iot.net:1883" //然也物联平台社区版 MQTT 服务器地址
#define CLIENTID "您的客户端 ID" //客户端 id
#define USERNAME "您的用户名" //用户名
#define PASSWORD "您的密码" //密码
/* 然也物联社区版 MQTT 服务为每个申请成功的用户
* 提供了个人专属主题级别，在官方发给您的微信信息中
* 提到了
* 以下 dt_mqtt/ 便是笔者的个人主题级别
* dt_mqtt 其实就是笔者申请社区版 MQTT 服务时注册的用户名
* 大家也是一样，所以你们需要替换下面的 dt_mqtt 前缀
* 换成你们的个人专属主题级别（也就是您申请时的用户名）
*/
#define WILL_TOPIC "dt_mqtt/will" //遗嘱主题
#define LED_TOPIC "dt_mqtt/led" //LED 主题
#define TEMP_TOPIC "dt_mqtt/temperature" //温度主题
/* ################################################# */
static int msgarrvd(void *context, char *topicName, int topicLen,MQTTClient_message *message) 
{
    if (!strcmp(topicName, LED_TOPIC)) 
    { //校验消息的主题
        if (!strcmp("2", message->payload)) //如果接收到的消息是"2"则设置 LED 为呼吸灯模式
            system("echo heartbeat > /sys/class/leds/input2::capslock/trigger");
        if (!strcmp("1", message->payload)) 
        { //如果是"1"则 LED 常量
            system("echo none > /sys/class/leds/input2::capslock/trigger");
            system("echo 1 > /sys/class/leds/input2::capslock/trigger");
        }   
        else if (!strcmp("0", message->payload)) 
        {//如果是"0"则 LED 熄灭
            system("echo none > /sys/class/leds/input2::capslock/trigger");
            system("echo 0 > /sys/class/leds/input2::capslock/trigger");
        }
        // 接收到其它数据 不做处理
    }
    /* 释放占用的内存空间 */
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    /* 退出 */
    return 1; 
}
static void connlost(void *context, char *cause) 
{
    printf("\nConnection lost\n");
    printf(" cause: %s\n", cause);
}
int main(int argc, char *argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_willOptions will_opts = MQTTClient_willOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    int rc;
    /* 创建 mqtt 客户端对象 */
    if (MQTTCLIENT_SUCCESS !=
    (rc = MQTTClient_create(&client, BROKER_ADDRESS, CLIENTID,
    MQTTCLIENT_PERSISTENCE_NONE, NULL))) 
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto exit;
    }
    /* 设置回调 */
    if (MQTTCLIENT_SUCCESS !=(rc = MQTTClient_setCallbacks(client, NULL, connlost,msgarrvd, NULL))) 
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }
    /* 连接 MQTT 服务器 */
    will_opts.topicName = WILL_TOPIC; //遗嘱主题
    will_opts.message = "Unexpected disconnection"; //遗嘱消息
    will_opts.retained = 1; //保留消息
    will_opts.qos = 0; //QoS0
    conn_opts.will = &will_opts;
    conn_opts.keepAliveInterval = 30; //心跳包间隔时间
    conn_opts.cleansession = 0; //cleanSession 标志
    conn_opts.username = USERNAME; //用户名
    conn_opts.password = PASSWORD; //密码
    if (MQTTCLIENT_SUCCESS !=
    (rc = MQTTClient_connect(client, &conn_opts))) 
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }
    printf("MQTT 服务器连接成功!\n");
    /* 发布上线消息 */
    pubmsg.payload = "Online"; //消息的内容
    pubmsg.payloadlen = 6; //内容的长度
    pubmsg.qos = 0; //QoS 等级
    pubmsg.retained = 1; //保留消息
    if (MQTTCLIENT_SUCCESS !=
    (rc = MQTTClient_publishMessage(client, WILL_TOPIC, &pubmsg, NULL))) 
    {
        printf("Failed to publish message, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    }
    /* 订阅主题 dt_mqtt/led */
    if (MQTTCLIENT_SUCCESS !=
    (rc = MQTTClient_subscribe(client, LED_TOPIC, 0))) 
    {
        printf("Failed to subscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    }
    /* 向服务端发布芯片温度信息 */
    for ( ; ; ) 
    {
        MQTTClient_message tempmsg = MQTTClient_message_initializer;
        char temp_str[10] = {0};
        int fd;
        /* 读取温度值 */
        fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
        read(fd, temp_str, sizeof(temp_str));//读取 temp 属性文件即可获取温度
        close(fd);
        /* 发布温度信息 */
        tempmsg.payload = temp_str; //消息的内容
        tempmsg.payloadlen = strlen(temp_str); //内容的长度
        tempmsg.qos = 0; //QoS 等级
        tempmsg.retained = 1; //保留消息
        if (MQTTCLIENT_SUCCESS !=(rc = MQTTClient_publishMessage(client, TEMP_TOPIC, &tempmsg, NULL))) 
        {
            printf("Failed to publish message, return code %d\n", rc);
            rc = EXIT_FAILURE;
            goto unsubscribe_exit;
        }
        sleep(30); //每隔 30 秒 更新一次数据
    }
    unsubscribe_exit:
    if (MQTTCLIENT_SUCCESS !=(rc = MQTTClient_unsubscribe(client, LED_TOPIC))) 
    {
        printf("Failed to unsubscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    disconnect_exit:
        if (MQTTCLIENT_SUCCESS !=(rc = MQTTClient_disconnect(client, 10000))) 
        {
            printf("Failed to disconnect, return code %d\n", rc);
            rc = EXIT_FAILURE;
        }
    destroy_exit:
        MQTTClient_destroy(&client);
    exit:
        return rc; 
}