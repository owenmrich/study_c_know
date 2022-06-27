// sudo apt-get install cmake
// https://cmake.org/documentation/ //文档总链接地址

project(HELLO) //设置工程名
set(SRC_LIST main.c hello.c)  //设置变量
add_executable(hello ${SRC_LIST}) //增加一个执行

project(HELLO)
add_library(libhello hello.c) //制作lib库
    add_library(libhello SHARED hello.c) #生成动态库文件
    add_library(libhello STATIC hello.c) #生成静态库文件
add_executable(hello main.c)
target_link_libraries(hello libhello) //链接lib库

顶层 CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
project(HELLO)
add_subdirectory(libhello)
add_subdirectory(src)

src 目录下的main.c CMakeLists.txt
include_directories(${PROJECT_SOURCE_DIR}/libhello)
add_executable(hello main.c)
target_link_libraries(hello libhello)

libhello 目录下的hello.c hello.h CMakeLists.txt
add_library(libhello hello.c)
set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
顶层 CMakeLists.txt 中使用了 add_subdirectory 命令，该命令告诉 cmake 去子目录中寻找新的
CMakeLists.txt 文件并解析它；而在 src 的 CMakeList.txt 文件中，新增加了 include_directories 命令用来指明
头文件所在的路径，并且使用到了 PROJECT_SOURCE_DIR 变量，该变量指向了一个路径，从命名上可知，
该变量表示工程源码的目录。
和前面一样，进入到 build 目录下进行构建、编译，最终会得到可执行文件 hello build/src/hello和库
文件 libhello.a（build/libhello/libhello.a


