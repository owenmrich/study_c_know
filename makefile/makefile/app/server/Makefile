filename1 = $(wildcard ./*.c)
filename += $(wildcard ./*.cpp)
objects := $(patsubst %.c, %.o, ${filename1})
objects := $(patsubst %.cpp, %.o, ${filename})
obj-y += ${objects}