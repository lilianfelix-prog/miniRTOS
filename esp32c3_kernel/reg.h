#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT(x) ((uint32_t) 1U << (x))
#define REG(x) ((volatile uint32_t *) (x))
#define READ_REG(x)  (*(volatile uint32_t *) (x))
#define REG_WRITE(x, a) (*(volatile uint32_t *) (x) = (a))

#define C3_SYSTEM 0x600c0000
#define C3_SENSITIVE 0x600c1000
#define C3_INTERRUPT 0x600c2000
#define C3_EXTMEM 0x600c4000
#define C3_MMU_TABLE 0x600c5000
#define C3_AES 0x6003a000
#define C3_SHA 0x6003b000
#define C3_RSA 0x6003c000
#define C3_HMAC 0x6003e000
#define C3_DIGITAL_SIGNATURE 0x6003d000
#define C3_GDMA 0x6003f000
#define C3_ASSIST_DEBUG 0x600ce000
#define C3_DEDICATED_GPIO 0x600cf000
#define C3_WORLD_CNTL 0x600d0000
#define C3_DPORT_END 0x600d3FFC
#define C3_UART0 0x60000000
#define C3_SPI1 0x60002000
#define C3_SPI0 0x60003000
#define C3_GPIO 0x60004000
#define C3_FE2 0x60005000
#define C3_FE 0x60006000
#define C3_RTCCNTL 0x60008000
#define C3_IO_MUX 0x60009000
#define C3_RTC_I2C 0x6000e000
#define C3_UART1 0x60010000
#define C3_I2C_EXT 0x60013000
#define C3_UHCI0 0x60014000
#define C3_RMT 0x60016000
#define C3_LEDC 0x60019000
#define C3_EFUSE 0x60008800
#define C3_NRX 0x6001CC00
#define C3_BB 0x6001D000
#define C3_TIMERGROUP0 0x6001F000
#define C3_TIMERGROUP1 0x60020000
#define C3_SYSTIMER 0x60023000
#define C3_SPI2 0x60024000
#define C3_SYSCON 0x60026000
#define C3_APB_CTRL 0x60026000
#define C3_TWAI 0x6002B000
#define C3_I2S0 0x6002D000
#define C3_APB_SARADC 0x60040000
#define C3_AES_XTS 0x600CC000

// UART interface 0 or 1
typedef enum
{
    UART0,
    UART1
} UART_port;

// The addresses in this section are relative to UART Controller base address provided

// Register 26.1. UART_FIFO_REG (0x0000)
#define UART_FIFO_REG(i)   (C3_UART(i) + 0x00)
// rx = (REG(UART_FIFO_REG(i)) & UART_RXFIFO_RD_BYTE);
// accesses FIFO via the field 0-7 bytes with bit mask
#define UART_RXFIFO_RD_BYTE  0x000000FF


#define UART_CLKDIV_REG(i)   (C3_UART(i) + 0x14)
#define UART_CLKDIV_FRAG  0x0000000F
#define UART_CLKDIV  0x00000FFF

#define UART_CONF0_REG(i)   (C3_UART(i) + 0x20)
#define UART_MEM_CLK_EN  (BIT(28))
/*description: Set this bit to reset the uart transmit-FIFO.*/
#define UART_TXFIFO_RST  (BIT(18))
/*description: Set this bit to reset the uart receive-FIFO.*/
#define UART_RXFIFO_RST  (BIT(17))
/*enable flow control for transmitter*/
#define UART_TX_FLOW_EN  (BIT(15))
/*set stop bit length*/
#define UART_STOP_BIT_NUM  0x00000003
/*set data length*/
#define UART_BIT_NUM  0x00000003
/*set parity*/
#define UART_PARITY  (BIT(0))

#define UART_CLK_CONF_REG(i)   (C3_UART(i) + 0x78)
/*description: Write 1 then write 0 to this bit  reset UART Rx.*/
#define UART_RX_RST_CORE  (BIT(27))
/*description: Write 1 then write 0 to this bit  reset UART Tx.*/
#define UART_TX_RST_CORE  (BIT(26))
/*description: Set this bit to enable UART Rx clock.*/
#define UART_RX_SCLK_EN  (BIT(25))
/*description: Set this bit to enable UART Tx clock.*/
#define UART_TX_SCLK_EN  (BIT(24))
/*description: Write 1 then write 0 to this bit  reset UART Tx/Rx.*/
#define UART_RST_CORE  (BIT(23))
/*description: Set this bit to enable UART Tx/Rx clock.*/
#define UART_SCLK_EN  (BIT(22))
/*description: UART clock source select. 1: 80Mhz  2: 8Mhz  3: XTAL.*/
#define UART_SCLK_SEL ((0x3)<<(20))
/*description: The integral part of the frequency divider factor.*/
#define UART_SCLK_DIV_NUM  ((0xFF)<<(12))
/*description: The numerator of the frequency divider factor.*/
#define UART_SCLK_DIV_A  ((0x3F)<<(6))
/*description: The  denominator of the frequency divider factor.*/
#define UART_SCLK_DIV_B  0x0000003F