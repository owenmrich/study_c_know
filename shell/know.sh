#!/bin/bash 

#../listener.sh 引用其他shell脚本
.<<!
多行注释
command > file	将输出重定向到 file。
command < file	将输入重定向到 file。
command >> file	将输出以追加的方式重定向到 file。
n > file	将文件描述符为 n 的文件重定向到 file。
n >> file	将文件描述符为 n 的文件以追加的方式重定向到 file。
n >& m	将输出文件 m 和 n 合并。
n <& m	将输入文件 m 和 n 合并。
<< tag	将开始标记 tag 和结束标记 tag 之间的内容作为输入。
!

.<<!
-eq	检测两个数是否相等，相等返回 true。	[ $a -eq $b ] 返回 false。
-ne	检测两个数是否不相等，不相等返回 true。	[ $a -ne $b ] 返回 true。
-gt	检测左边的数是否大于右边的，如果是，则返回 true。	[ $a -gt $b ] 返回 false。
-lt	检测左边的数是否小于右边的，如果是，则返回 true。	[ $a -lt $b ] 返回 true。
-ge	检测左边的数是否大于等于右边的，如果是，则返回 true。	[ $a -ge $b ] 返回 false。
-le	检测左边的数是否小于等于右边的，如果是，则返回 true。	[ $a -le $b ] 返回 true。
!

.<<!
test 命令用于检查某个条件是否成立，它可以进行数值、字符和文件三个方面的测试。 
#数值
-eq	等于则为真
-ne	不等于则为真
-gt	大于则为真
-ge	大于等于则为真
-lt	小于则为真
-le	小于等于则为真
#字符
=	等于则为真
!=	不相等则为真
-z 字符串	字符串的长度为零则为真
-n 字符串	字符串的长度不为零则为真
#文件
-e 文件名	如果文件存在则为真
-r 文件名	如果文件存在且可读则为真
-w 文件名	如果文件存在且可写则为真
-x 文件名	如果文件存在且可执行则为真
-s 文件名	如果文件存在且至少有一个字符则为真
-d 文件名	如果文件存在且为目录则为真
-f 文件名	如果文件存在且为普通文件则为真
-c 文件名	如果文件存在且为字符型特殊文件则为真
-b 文件名	如果文件存在且为块特殊文件则为真
!
# ` ` 调用shell 函数
# expr 加减乘除
CURDATE= `date` #反单引号 = $()
printf "i wanna get the date, output like this?\n  %s\n" '$CURDATE'
echo -e "no! just output like this: \n $CURDATE"#-e 转义,可以在echo中加入\n

echo -e "the hostname is: \n$(hostname)"#显示主机名
echo -e "the current user is: \n$(whoami)"#用于显示自身用户名
echo -e "the os info is: \n$(uname -a)"#显示当前系统相关信息
echo -e "the process info is: \n$(ps -u)"#在普通用户模式下root权限可以查看进程
echo -e "the disk status is: \n$(du -sh/home)"#显示/home目录下,磁盘的使用情况

#.  代表当前目录
#.. 代表父目录
#~  代表home目录

# mkdir file  创建文件目录
# touch file1 创建文件
# \           续行符
# cp file1 file2 复制文件
# mv file1 file2 剪切文件
# cat 获取文件内容
# $?  用来获取上个命令的返回值
# rm  -r删除目录
# chmod a+x shell.sh a+x 表示为所有用户增加执行权限
# 写脚本的注意事项
# 1.等号赋值两边不能有空格
# 2.命令于选项之间需要空格; [ "$sd" ]
# 3.管道两边空格可有可无

# if [ ... ]; then
#       dosomwthing
# else if [ ... ];then
#       dosomwthing
# else
#       dosomwthing
# fi

# while [ ... ]; do
#    dosomwthing
# done
# for 变量 in 列表;do
#      dosomwthing
# done

# case 变量 in:
#   情况)
#   dosomwthing
#   ;;
#   情况)
#   dosomwthing
#   ;;
#   *)
#   ;;
# esac

# trap 
# trap `command` signal  command命令 signal 通常为EXIT ERR DEBUG
# EXIT:终止shell 输出跟踪变量的值 ERR:追踪执行不成功的命令或者是函数，并输出相关的调试信息
# DEBUG: 追踪变量 echo打印

# function ...(){
#   command1
#   command2
#   [return value]函数返回值,可以显示增加return语句;如果不加,则将最后一条命令运行结果作
#   为返回值(一般为0，如果执行失败则返回错误代码)，return 后跟数值( 0-255 ).
#   }

# [vmstat ]是用于统计虚拟内存信息的命令,可以对操作系统的proc、memory.CPU、I0等信息进行统计以呈现给用户。
# vmstat 1 5 每1秒打印一次，共5次
# [管道]管道是Shell中比较常用的一个将命令串起来的方法, 通过管道将前一个命令
# 的输出作为后一个命令的输入。Shell 中的管道符号是[|]
# vmstat 1 5 | sed -n '3,$p' 这个代码段中的管道的含义就是将vmstat 1 5打印的结果传输到下一条命令中

# sed 管道命令，主要以行为单位进行处理，可以对数据行进行替换，删除，新增，选取
# sed -n '3,$p' -n 只显示经过sed处理的行 3第三行 p打印行
# sed "s/被替换的字符/替换字符"
# s命令是表示用一个字符串替换另一个字符串。
# g命令表示全文替换,如果不加g则只替换行内的第一个字符串。
# ^符号的意思是指行首字符串。

# awk 倾向于一行当中分成数个域来处理
# awk `条件1{动作1} 条件2{动作2}`
# cat arp.txt | awk`gsub(/\(/,b)gsub(/\)/,b)gsub(/:/,b) {print $4，$2}` 
# gsub 匹配所有的符合模式的字符串 gsub(/\(/,b)) 把"( "替换为不可见字符"b"

# grep -m 1 -w "HWaddr" 一次查找一个保函"HWaddr"的字符串，
# -m 1 一次匹配一个 -w 全词查找
 
 # 重定向 
 # 输出重定向command > 从头开始写入     command >> 追加加入
 # command < 一个文件直接输入数据

 # 脚本调试 tee 
 # tee [文件名] 例:tee cpu_tee 可以将上步的值保存于文本中,便于脚本管道消息调试
