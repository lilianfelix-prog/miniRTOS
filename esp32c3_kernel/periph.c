#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "periph.h"

void UART_Init(UART_t* uart_init)
{
    uart_init->uart_port = UART0;
    uart_init->uart_baudrate = 9600; //default baudrate of 9600
    uart_init->uart_data_length = ((uint16_t)0x0000); //default data length of 8b
    uart_init->uart_stop_bits = ((uint16_t)0x0000); 
    uart_init->uart_parity = ((uint16_t)0x0000); //no parity
    uart_init->uart_mode = UART_MODE_UART; //UART_Mode_Rx | UART_Mode_Tx;
    uart_init->uart_flowcontrol = UART_HW_FLOWCTRL_DISABLE;
}