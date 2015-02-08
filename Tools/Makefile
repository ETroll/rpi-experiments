
GO = go
MAKE = make

SDCARD = Sdcard/
SUBDIRS = Bootloader

.PHONY: sdcard $(SUBDIRS)

all:
	$(SUBDIRS)

$(SUBDIRS):
	echo $(MAKE) -C $@

sdcard:
	mkdir -p $(SDCARD)
	cp config.txt $(SDCARD)
	cd $(SDCARD); curl -o start.elf https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/start.elf
	cd $(SDCARD); curl -o bootcode.bin https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/bootcode.bin
	cd $(SDCARD); curl -o fixup.dat https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/fixup.dat
