#产生目标文件
obj-m:=kretprobe_example.o
#路径变量，指明当前路径
CURRENT_PATH:=$(shell pwd)
#指明内核版本号
LINUX_KERNEL:=$(shell uname -r)
#指明内核源码的绝对路径
LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)
#编译模块
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
#清理模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	


