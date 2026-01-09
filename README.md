# miniRTOS

**This is a simple RTOS built for the ESP32-C3.**  

The project is primarily a learning exercise in low-level system
bring-up on a RISC-V microcontroller. Building it required working
directly with the ESP32-C3 boot process, memory layout, control and
status registers (CSRs), and peripheral registers without relying on
vendor frameworks.

The goal is to understand how higher-level abstractions such as an RTOS
are constructed from bare-metal components, starting with clocks,
interrupts, timers, and basic I/O.

The design and implementation of this project are strongly influenced by
the ESP-IDF framework and the ESP32-C3 technical reference manual, which
served as primary references.

 Currently implemented components:
 - Startup code and memory layout (linker script)
 - Minimal RISC-V system register access (status and interrupt control)
 - System timer (SYSTIMER) configuration and clock source for machine time
 - Basic UART configuration with character-level FIFO read/write
 - GPIO initialization

### Developement: 

Tools: 
- `pip install esptool`
- `git clone https://github.com/espressif/esp-idf`

Source ESP_IDF environment for path to idf.py, python venv, toolchains:
- `. ~/esp-idf/export.sh`

Activate esptool venv:
- `source miniRTOS-venv/bin/activate`

