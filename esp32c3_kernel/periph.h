#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clk_def.h"
#include "reg.h"
/*
 * Register 5.21. IO_MUX_GPIOn_REG (n: 0-21) (0x0004+4*n) 
 * (following specs sheet) offsets for GPIOs from IO MUX base 
 */ 
#define C3_MUX_GPIO0_REG (C3_IO_MUX + 0x04)
#define C3_MUX_GPIO1_REG (C3_IO_MUX + 0x08)
#define C3_MUX_GPIO2_REG (C3_IO_MUX + 0x0c)
#define C3_MUX_GPIO3_REG (C3_IO_MUX + 0x10)
#define C3_MUX_GPIO4_REG (C3_IO_MUX + 0x14)
#define C3_MUX_GPIO5_REG (C3_IO_MUX + 0x18)
#define C3_MUX_GPIO6_REG (C3_IO_MUX + 0x1c)
#define C3_MUX_GPIO7_REG (C3_IO_MUX + 0x20)
#define C3_MUX_GPIO8_REG (C3_IO_MUX + 0x24)
#define C3_MUX_GPIO9_REG (C3_IO_MUX + 0x28)
#define C3_MUX_GPIO10_REG (C3_IO_MUX + 0x2c)
#define C3_MUX_GPIO11_REG (C3_IO_MUX + 0x30)
#define C3_MUX_GPIO12_REG (C3_IO_MUX + 0x34)
#define C3_MUX_GPIO13_REG (C3_IO_MUX + 0x38)
#define C3_MUX_GPIO14_REG (C3_IO_MUX + 0x3c)
#define C3_MUX_GPIO15_REG (C3_IO_MUX + 0x40)
#define C3_MUX_GPIO16_REG (C3_IO_MUX + 0x44)
#define C3_MUX_GPIO17_REG (C3_IO_MUX + 0x48)
#define C3_MUX_GPIO18_REG (C3_IO_MUX + 0x4c)
#define C3_MUX_GPIO19_REG (C3_IO_MUX + 0x50)
#define C3_MUX_GPIO20_REG (C3_IO_MUX + 0x54)
#define C3_MUX_GPIO21_REG (C3_IO_MUX + 0x58)


#define UART_Mode_Rx                        ((uint16_t)0x0004)
#define UART_Mode_Tx                        ((uint16_t)0x0008)

typedef enum
{
    SOC_MOD_CLK_APB,
    SOC_MOD_CLK_XTAL,

} GPIOSpeed_t;


typedef struct 
{
    uint16_t gpio_pin;
    GPIOSpeed_t gpio_speed;

} GPIO_t;

typedef enum
{
    UART_MODE_UART = 0x00,  // only use regular for now

} UARTMode_t; 

// UART hardware flow control modes, controls txd_out and rxd_in data flows
typedef enum
{
    UART_HW_FLOWCTRL_DISABLE = 0x0, 
    UART_HW_FLOWCTRL_CTS_RTS = 0x3,
} UARTHW_t;

typedef struct 
{
    UART_port uart_port;
    uint32_t uart_baudrate; 
    uint16_t uart_data_length;
    uint16_t uart_stop_bits; 
    uint16_t uart_parity;
    UARTMode_t uart_mode;
    UARTHW_t uart_flowcontrol;

} UART_t;

static inline void uart_set_sclk(soc_periph_uart_clk_src_legacy_t src)
{

}
