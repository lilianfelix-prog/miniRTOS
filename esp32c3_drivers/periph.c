#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg.h"
#include "system.h"

#define U0RXD_GPIO_NUM GPIO20
#define U0TXD_GPIO_NUM GPIO21

typedef struct 
{
    uint32_t uart_baudrate; 
    uint16_t uart_data_length;
    uint16_t uart_stop_bits; 
    uint16_t uart_parity;
    uint16_t uart_mode;
    uint16_t uart_flowcontrol;
    UART_port uart_port;

} UART_t;

const uint32_t sys_clk_hz = 80000000;
const uint32_t baud = 9600;

void UART_Def_Config(UART_t* uart_def)
{
    uart_def->uart_port = UART0;
    uart_def->uart_baudrate = baud; //default baudrate of 9600
    uart_def->uart_data_length = UART_DATA_8_BITS; //default data length of 8b
    uart_def->uart_stop_bits = UART_STOP_BITS_1; 
    uart_def->uart_parity = UART_PARITY_DISABLE; //no parity
    uart_def->uart_mode = 0x00; 
    uart_def->uart_flowcontrol = 0x00;
}

void UART_Init(UART_t* uart_def)
{
    //Enable periph clk
    uart_set_periph_clk(ENABLE);
    //Select clock source
    uart_set_clk_source(uart_def->uart_port, UART_SCLK_XTAL);
    // enable tx/rx clock
    uart_set_clock(uart_def->uart_port, ENABLE);
    //Reset uart core
    uart_reset_core(uart_def->uart_port);

    //Set baudrate divider
    uart_set_baudrate(uart_def->uart_port, sys_clk_hz, uart_def->uart_baudrate);
    //Set data bits
    uart_set_data_bits(uart_def->uart_port, uart_def->uart_data_length);
    //Set stop bit
    uart_set_stop_bit(uart_def->uart_port, uart_def->uart_stop_bits);
    //Set parity 
    uart_set_parity(uart_def->uart_port, uart_def->uart_parity);

    //Rest TX/RX FIFO
    uart_rst_tx_fifo(uart_def->uart_port);
    uart_rst_rx_fifo(uart_def->uart_port);
    //Set TX threshold val for empty fifo
    set_txfifo_empty_thr(uart_def->uart_port, 0x3); // interupt when fifo > 0011

    //Disable flowcontrol
    uart_enable_flow_control(uart_def->uart_port, DISABLE);

    //Configure gpio21 for UART TX
    gpio_enable_pin(U0TXD_GPIO_NUM, ENABLE);
    
    //turn on clk for TX/RX
    uart_set_clk_on(uart_def->uart_port, ENABLE);
}


void main(void)
{
    UART_t uart_0;
    UART_Def_Config(&uart_0);
    UART_Init(&uart_0);

    const uint8_t buffer[] = "Hello\n";
    
    uart_write_txfifo(uart_0.uart_port, buffer, sizeof(buffer)-1);

    while(1) { }
}
