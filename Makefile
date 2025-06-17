OUTPUT_DIR := ./build
IMAGE := miniRTOS.elf

CC = riscv64-unknown-elf-gcc
SIZE = riscv64-unknown-elf-size

MARCH=rv32imac_zicsr
MADI=ilp32
MCMODEL=medlow

INCLUDE_DIRS += -I./kernel/chip_specific_extensions/RV32I_CLINT_no_extensions

#see RV32I compile flags
CFLAGS += $(INCLUDE_DIRS) -march=$(MARCH) -mabi=$(MABI) -mcmodel=$(MCMODEL) \
		--specs=nosys.specs -fno-builtin-printf

LDFLAGS += -nostartfiles -Xlinker --gc-sections -Wl -MAP, ./build/miniRTOS.map \
		-T./linker.ld -march=$(MARCH) -mabi=$(MABI) -mcmodel=$(MCMODEL) -Xlinker \
		--defsym=__stack_size=352 -Wl, --start-group -Wl, --end-group


KERNEL_PORT_DIR += ./kernel/portable
INCLUDE_DIR += ./include

SOURCE_FILES += ./kernel/task_handler.c
SOURCE_FILES += ./kernel/heap_1.c
ASM_SOURCE_FILES += $(KERNEL_PORT_DIR)/portASM.S
ASM_SOURCE_FILES += ./startup.S

OBJS = $(SOURCE_FILES:%.c=%.o) $(ASM_SOURCE_FILES:%.S=%.o)
OBJS_NO_PATH = $(notdir $(OBJS))
OBJS_OUTPUT = $(OBJS_NO_PATH:%.o=$(OUTPUT_DIR)/%.o)


DEP_FILES = $(SOURCE_FILES:%.c=%.d) $(ASM_SOURCE_FILES:%.S=%.d)
DEP_FILES_NO_PATH = $(notdir $(DEP_FILES))
DEP_OUTPUT = $(DEP_FILES_NO_PATH:%.d=$(OUTPUT_DIR)/%.d)

all: $(OUTPUT_DIR)/$(IMAGE)

%.o : %.c
$(OUTPUT_DIR)/%.o : %.c $(OUTPUT_DIR)/%.d Makefile 
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.o : %.S 
$(OUTPUT_DIR)/%.o : %.S $(OUTPUT_DIR)/%.d Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OUTPUT_DIR)/$(IMAGE): $(OBJS_OUTPUT) Makefile
	$(CC) $(OBJS_OUTPUT) $(LDFLAGS) -o $(OUTPUT_DIR)/$(IMAGE)
	$(SIZE) $(OUTPUT_DIR)/$(IMAGE)

clean:
	rm -f $(OUTPUT_DIR)/$(IMAGE) $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/*.d $(OUTPUT_DIR)/*.map 

.PHONY: all clean