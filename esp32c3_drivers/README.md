## Debug driver with openOCD via JTAG:
Can't use flash memory yet (rom not mapped and no flash config), so everything is directly loaded on device iram/dram for debug.

* Start esp32c3 openocd jtag interface: `sudo penocd -f interface/esp_usb_jtag.cfg -f target/esp32c3.cfg`  
* Open the driver.elf with gdb: `riscv32-esp-elf-gdb build/driver.elf`
* GDB: `target remote :3333` 
* GDB: `monitor reset halt`
* GDB: `load`
* GDB: `break _start`
* GDB: `break main`
* GDB: `continue`
* GDB: `stepi`
* GDB: `info registers`
* GDB: `disassemble /m $pc-32, $pc+32`
