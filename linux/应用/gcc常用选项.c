-E  预处理开发过程中想快速确定某个宏可以使用"-E -dM"
-c  把预处理、编译、汇编都做了，但是不链接
-o  指定输出文件.
-I  指定头文件日录
-L  指定链接时库文件日录
-l  指定链接哪一个库文件
    -lxxx  指定的lib目录下查找
           或者是-L 指定目录下查找
#include"sb.h"    :当前目录下查找
#include<stdio.h> :工具链默认目录下查找
#include<sb.h>    :就需要加入  -I ./  来指定目录

制作使用静态库
gcc -c -o main.o main.c
gcc -c -o sub.o sub.c
ar crs libsub.a sub.o sub2.o sub3.o (可以使用多个.o生成静态库)
gcc -o test main.o libsub.a (如果.a不在当前目录下,需要指定它的绝对或相对路径)
会将静态库与main.o 打包一起,文件会比较大

制作使用动态库
gce -c -o main.o main.c
gcc -c -o sub.o sub.c
gcc -shared -o libsub.so sub.o  sub2.o sub3.o (可以使用多个.o生成动态库)
gcc -o test main.o -lsub -L /libsuh.so/所在目录/

gcc -E main. C//查看预处理结果，比如头文件是哪个
gcc -E -dM main. C > 1.txt//把所有的宏展开存在1.txt里
gcc -Wp, -MD, abc. dep -c -o main.o main.c // 生成依赖文件abc. dep,后面Makefile会用
echo 'main() {}' | gcc -E -v - //它会列出头文件目录、库目录(LIBRARY_ _PATH)


