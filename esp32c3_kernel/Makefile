CROSS_COMPILE = riscv32-esp-elf-

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as

CFLAGS = -march=rv32imc_zicsr -mabi=ilp32 -ffreestanding -nostdlib -Wall
LDFLAGS = -T linker.ld -nostdlib -lgcc

BUILD_DIR = build
TARGET = $(BUILD_DIR)/driver.elf

SRCS = periph.c boot.S
OBJS = $(BUILD_DIR)/periph.o $(BUILD_DIR)/boot.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/periph.o: periph.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/boot.o: boot.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
