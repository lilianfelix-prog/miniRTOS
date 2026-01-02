CROSS_COMPILE = riscv64-linux-gnu-
CC = riscv64-unknown-elf-gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld

BUILD_DIR = build

# Output
TARGET = $(BUILD_DIR)/timer

all: $(TARGET)

# Final link
$(TARGET): $(BUILD_DIR)/timer.o $(BUILD_DIR)/boot.o kernel_linker.ld
	$(LD) -T kernel_linker.ld --no-dynamic-linker -static -nostdlib \
		-o $(TARGET) $(BUILD_DIR)/timer.o $(BUILD_DIR)/boot.o

# Assemble boot
$(BUILD_DIR)/boot.o: boot.s | $(BUILD_DIR)
	$(AS) -march=rv64i -mabi=lp64 -o $(BUILD_DIR)/boot.o boot.s

# Assemble timer
$(BUILD_DIR)/timer.o: $(BUILD_DIR)/timer.s | $(BUILD_DIR)
	$(AS) -march=rv64i -mabi=lp64 -o $(BUILD_DIR)/timer.o $(BUILD_DIR)/timer.s

# Compile C → assembly
$(BUILD_DIR)/timer.s: timer.c | $(BUILD_DIR)
	$(CC) -march=rv64i_zicsr -mabi=lp64 -S timer.c -o $(BUILD_DIR)/timer.s

# Make sure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean generated files
clean clear:
	rm -rf $(BUILD_DIR)