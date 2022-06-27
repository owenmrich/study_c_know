#!/bin/bash
trap 'echo "before execute line: $LINENO, NUM=$NUM, CPU=$CPU"' DEBUG
function Getcpu
{
    CpuIdle=`vmstat 1 5 | sed -n '3,$p' \
    | tee cpu_tee | awk '{x = + $15} END {print x/5}' | awk -F. '{print $1}'`
    CpuNum=`echo "100-$CpuIdle" | bc` #bc字符串内容进行减法运算
    echo $CpuNum
}
NUM=3
export LOGNAME=Owen_vmware #给环境变量LOGNAME赋值
while [ $NUM -gt 0 ]; do #循环3次
    CPU=`Getcpu`
    DATE=`date`
    if [ $CPU -gt 90 ]; then #cpu负载值(-gt)大于90
        RESULT=2
        (
            MAC=`ifconfig | grep -m 1 -w "HWaddr" | awk '{print $5}'`
            echo "CPU High Using Waring!the logname is: $LOGNAME ***the MAC of this pc is: $MAC***the system is: $DATE" >> log
        )
    elif [ $CPU -lt 10 ]; then #cpu负载值(-lt)小于10
        RESULT=0
        (
            MAC=`ifconfig | grep -m 1 -W "HWaddr" | awk '{print $5}'`
            echo "CPU low Using Waring!the logname is: $LOGNAME ***the MAC of this pc is: $MAC***the system is: $DATE" >> log
        )
    else #正常cpu的负载值
        RESULT=1
    fi
    case $RESULT in
        "2" )
        printf "Hello %s, The Usage Of SystemCpu Is %s, Too High! \n Syster
        date is:%s\n" "$LOGNAME" "$CPU" "$DATE" #CPU负载过高提示
        ;;
        "O" )
        echo "Hello $LOGNAME, The Usage of System Cpu Is $CPU, Too low! \nSystem Date is: $DATE" #CPU负载过低提示
        ;;
        "1")
        echo "Hello $LOGNAME, The Usage Of System Cpu Is $CPU,Normal ! \nSystem Date Is: $DATE"
        ;;
        *)
        ;;
    esac #根据不同的负载情况分别向系统管理员打印相应情况
    NUM=`expr $NUM - 1` #NUM- 1
    sleep 5 #休眠5秒
done 
