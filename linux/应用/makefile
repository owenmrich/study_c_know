目标文件:依赖文件
	命令          #当依赖比目标新执行命令
test:a.o b.o
	gcc -o test $^
a.o:a.c
	gcc -c -o a.o a.c
b.o:b.c
	gcc -c -o b.o b.c
.PHONY clean
clean:
	rm *.o test

通配符%.o
c.o:c.o c.h
%.o:%.c
	gcc -c -o $@ $^   # $@ 目标文件 $^ 所有的依赖

假想目标
.PHONY clean

make 命令参数放在那里都可以,重复出现的值会把前面的值覆盖
make d=123 #通过命令行存入变量
赋值方法 
A = a v b  #代表A里面有三个值，用空格隔开
简单变量(即时变量) :
A:=xxx      #A的值即刻确定，在定义时即确定
B =xxx      #B的值使用到时才确定
:=          #即时变量
=           #延时变量
?=          #延时变量,如果是第1次定义于起效,如果在前面该变量已定义则忽略这句
+=          #附加，它是即时变量还是延时变量取决于前面的定义

make常用函数 


$(foreach var, list, text)
	B=$(foreach f,$(A),$(f).o) #把文件变为.o文件

$(filter pattern, text)   #在text中取出符合patten格式的值
$(filter-out pattern, text) #在text中取出不符合patten格式的值
	C=$(filter %/, $(c))  #取出目录

$(wildcard pattern) #pattern定义了文件名的格式 wildcard取出其中存在的文件
	files = $(wildcard *.c) #当前目录下符合*.c的文件 把文件的名字赋值给files
	file1 = $(wildcard $(file)) #查找file中真实存在的文件

$(patsubst pattern, replacement, $(var)) #在text中取出符合patten格式的值替换为replacement
	dep_file = $(patsubst %.c, %.o, $(file))

gcc生成依赖
	gcc -M c.c   #可以获得c.c的依赖
	gcc -M -MF c.d c.c #可以获得c.c的依赖并生成一个文件c.d 来存放依赖
	gcc -c -o c.o c.c -MD -MF c.d

objs = a.o b.o c.o
dep_files := $(patsubst %, .%.d, $(objs))
dep_files := $(wildcard $(dep_files))
CFLAGS = -Werror -I ./include
test: $(objs)
gcc -o test $^
ifneq ($(dep_files),)
include $(dep_files)
endif
%.o :%.c
gcc $(CFLAGS)-c -o $@ $< -MD -MF  .$@.d
clean:
rm *.o test
distclean :
	rm $(dep_files)
.PHONY : clean


