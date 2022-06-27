#!/bin/bash
if [ $# -ne 1 ]; then
    echo "please input the right partment"
    exit 1
fi
# $# 代表脚本输入的参数个数
# -ne 表示不等号
trap 'echo "before execute line: $LINENO, NUM=$NUM"' DEBUG
NUM=3 
CPU=$1 #获取cpu 负载值
DATE=`date` #获得系统日期
export LOGNAME=Owen_vmware #给环境变量LOGNAME赋值
while [ $NUM -gt 0 ]; do #循环3次
    if [ $CPU -gt 90]; then #cpu负载值(-gt)大于90
        RESULT=2
    elif [ $CPU -lt 10 ]; then #cpu负载值(-lt)小于10
        RESULT=0
    else #正常cpu的负载值
        RESULT=1
    fi
    case $RESULT in
        "2" )
        printf "Hello %s, The Usage Of SystemCpu Is %s, Too High! \nSyster
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
