# Hello world kernel module

EXTRA_CFLAGS = -Wall
obj-m = main.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
    make -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS=$(EXTRA_CFLAGS)

clean:
    make -C $(KDIR) M=$(PWD) clean

change:
    sudo chmod 0666 /dev/my_device

rm:
    sudo rmmod main

view:
    dmesg | tail

cat:
    cat /dev/my_device

run:
    sudo insmod main.ko
