
#!/bin/bash
#file:hw.sh
#author:吴其亮
#describe: 打开日志信息匹配错误信息，将错误信息对应的mac，ip出来
function findarp
{
    #获取设备地址的临时文件
    #arp -a | awk 'gsub(/\(/,b)gsub(/\)/,b)gsub(/:/,b) {print $4,$2}' > arp_tmp.txt
    cat arp.txt | awk 'gsub(/\(/,b)gsub(/\)/,b)gsub(/:/,b) {print $4,$2}' > arp_tmp.txt
}
function find_error_mac()
{
    #把error_kmsg.tmp 错误的文件名中获取mac
    if [ -s error_kmsg.tmp ]; then
        error_mac_kmsg=`cut -c8-19 error_kmsg.tmp | tee error_mac_kmsg.txt`
        #获得错误出现的时间
        error_time_kmsg=`cut -d '[' -f 2 error_kmsg.tmp | cut -d ']' -f 1 | tee error_time_kmsg.txt`
    fi
    #把error_logcat.tmp 错误的文件名中获取mac
    if [ -s error_logcat.tmp ]; then
        error_mac_logcat=`cut -c8-19 error_logcat.tmp | tee error_mac_logcat.txt`
        error_time_logcat=`cut -c35-52 error_logcat.tmp | tee error_time_logcat.txt`
    fi
}
function finderror_kmsg()
{
    #寻找有错误的*_kmsg文件
    error=`find ./logs/ -name "*_kmsg" | xargs grep -w "GPU fault" -rn | tee error_kmsg.tmp`
    #寻找有错误的*_logcat文件
    error1=`find ./logs/ -name "*_logcat" | xargs grep -w "GL error 0x0505" -rn | tee error_logcat.tmp`
}
function find_error_ip()
{
    #通过mac 寻找对应ip 并打印ip mac  
    echo "===========" >> error_kmsg
    echo "ip             mac          uptime of first error               error type" >> error_kmsg
    for GREP_RESULT in $error_mac_kmsg; do
        cat arp_tmp.txt | grep ${GREP_RESULT} >> mac_ip
    done
    for GREP_RESULT in $error_mac_kmsg; do
        paste -d ' ' mac_ip error_time_kmsg.txt | grep ${GREP_RESULT} | awk '{print $2,$1,$3}' >> error_kmsg
    done

    #此为logcat部分
    echo "==========" >> error_logcat
    echo "ip             mac          uptime of first error               error type" >> error_logcat
    for GPU_RESULT in $error_mac_logcat; do
        cat arp_tmp.txt | grep ${GPU_RESULT} >> mac_ip1
    done
    for GPU_RESULT in $error_mac_logcat; do
        paste -d ' ' mac_ip1 error_time_logcat.txt | grep ${GPU_RESULT} | awk '{print $2,$1,$3}' >> error_logcat
    done 
}
while [ 1 ]; do
    findarp
    finderror_kmsg
    find_error_mac
    find_error_ip

    rm *.tmp
    rm mac*
    rm error_mac*
    rm error_time*

    sleep 1h
done
