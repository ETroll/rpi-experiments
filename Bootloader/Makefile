ARMGNU ?= arm-none-eabi
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding

OBJECT = Obj/
SOURCE = ./
BUILD = Bin/

TARGET = kernel.img
LIST = kernel.list
MAP = kernel.map
HEX = kernel.hex

LINKER = kernel.ld


OBJECTS_AS := $(patsubst $(SOURCE)%.s,$(OBJECT)%.o,$(wildcard $(SOURCE)*.s))
OBJECTS_GCC := $(patsubst $(SOURCE)%.c,$(OBJECT)%.o,$(wildcard $(SOURCE)*.c))


OBJECTS_ALL += $(OBJECTS_AS)
OBJECTS_ALL += $(OBJECTS_GCC)

rebuild: clean all

all: $(TARGET) $(LIST) $(HEX)

$(LIST) : $(OBJECT)output.elf
	$(ARMGNU)-objdump -D $(OBJECT)output.elf > $(BUILD)/$(LIST)

$(TARGET) : $(OBJECT)output.elf
	$(ARMGNU)-objcopy $(OBJECT)output.elf -O binary $(BUILD)/$(TARGET)

$(HEX) : $(OBJECT)output.elf
	$(ARMGNU)-objcopy $(OBJECT)output.elf -O ihex $(BUILD)/$(HEX)

$(OBJECT)output.elf : $(OBJECTS_AS) $(OBJECTS_GCC) $(LINKER) $(BUILD)
	$(ARMGNU)-ld --no-undefined $(OBJECTS_ALL) -Map $(BUILD)/$(MAP) -o $(OBJECT)output.elf -T $(LINKER)

$(OBJECTS_AS): $(OBJECT)
	$(ARMGNU)-as $(patsubst $(OBJECT)%.o, $(SOURCE)%.s, $@) -o $@

$(OBJECTS_GCC): $(OBJECT)
	$(ARMGNU)-gcc $(COPS) -std=c99 -c $(patsubst $(OBJECT)%.o, $(SOURCE)%.c, $@) -o $@

$(OBJECT):
	mkdir $@

$(BUILD):
	mkdir $@

# Rule to clean files.
clean :
	-rm -rf $(OBJECT)
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
