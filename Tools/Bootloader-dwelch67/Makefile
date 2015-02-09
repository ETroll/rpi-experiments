
ARMGNU ?= arm-none-eabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding

all : kernel.img

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc


vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

bootloader.o : bootloader.c
	$(ARMGNU)-gcc $(COPS) -c bootloader.c -o bootloader.o

periph.o : periph.c
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

kernel.img : loader vectors.o periph.o bootloader.o
	$(ARMGNU)-ld vectors.o periph.o bootloader.o -T loader -o bootloader.elf
	$(ARMGNU)-objdump -D bootloader.elf > bootloader.list
	$(ARMGNU)-objcopy bootloader.elf -O ihex bootloader.hex
	$(ARMGNU)-objcopy bootloader.elf -O binary kernel.img
