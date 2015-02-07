
GO = go

SDCARD = Sdcard/
SUBDIRS = Bootloader

.PHONY: sdcard $(SUBDIRS)

all:
	$(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

sdcard:
	mkdir -p $(SDCARD)
	cp config.txt $(SDCARD)
	cd $(SDCARD); curl -O https://github.com/raspberrypi/firmware/blob/master/boot/start.elf
	cd $(SDCARD); curl -O https://github.com/raspberrypi/firmware/blob/master/boot/bootcode.bin
