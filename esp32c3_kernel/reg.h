#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clk_def.h"

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

typedef enum 
{
    DISABLE,
    UNABLE
} UART_state;
// The addresses in this section are relative to UART Controller base address provided
/*
 * How the register bit mask works:
 * UART_FIFO_REG & UART_REG_FLAG_MASK = (flag's register region according to specs)
 */

// Register 26.1. UART_FIFO_REG (0x0000)
#define UART_FIFO_REG(i)   (C3_UART(i) + 0x00)
// rx = (REG(UART_FIFO_REG(i)) & UART_RXFIFO_RD_BYTE);
// accesses FIFO via the field 0-7 bytes with bit mask
#define UART_RXFIFO_RD_BYTE  0x000000FF


#define UART_MEM_CONF_REG(i) (C3_UART(i) + 0x60)
#define UART_RX_SIZE  ((0x3)<<(1))
#define UART_TX_SIZE  ((0x3)<<(3))
#define UART_RX_FLOW_THRHD ((0x1FF)<<(7))


#define UART_INT_RAW_REG(i)   (C3_UART(i) + 0x4)
/*bit turns to 1 when receiver receives more data than what is in rxfifo_full_thrhd*/
#define UART_RXFIFO_FULL_INT_RAW  (BIT(0))
/*bit turns to 1 when tx fifo is less than txfifo_empty_thrhd*/
#define UART_TXFIFO_EMPTY_INT_RAW  (BIT(1))


#define UART_CLKDIV_REG(i)   (C3_UART(i) + 0x14)
/*integral part of the freq divisor*/
#define UART_CLKDIV_FRAG  0x0000000F
#define CLKDIV_FRAG_OFFSET 20
/*fractional part of the freq divisor*/
#define UART_CLKDIV  0x00000FFF
#define CLKDIV_OFFSET 0

#define UART_CONF0_REG(i)   (C3_UART(i) + 0x20)
#define UART_MEM_CLK_EN  (BIT(28))
#define MEM_CLK_EN_OFFSET 28
/*description: Set this bit to reset the uart transmit-FIFO.*/
#define UART_TXFIFO_RST  (BIT(18))
/*description: Set this bit to reset the uart receive-FIFO.*/
#define UART_RXFIFO_RST  (BIT(17))
/*enable flow control for transmitter*/
#define UART_TX_FLOW_EN  (BIT(15))
/*set stop bit length*/
#define UART_STOP_BIT_NUM  ((0x3)<<(4))
#define STOP_BIT_OFFSET 4
/*set data length*/
#define UART_BIT_NUM  ((0x3)<<(2))
#define BIT_NUM_OFFSET 2
/*set parity*/
#define UART_PARITY  (BIT(0))
#define PARITY_OFFSET 0


#define UART_CONF1_REG(i)  (C3_UART(i) + 0x24)
/*interupt when receiver data > this val*/
#define UART_RXFIFO_FULL_THRHD   ((0x1FF)(0))
#define FULL_THR_OFFSET 0x0
/*interupt when tx fifo is less then this val*/
#define UART_TXFIFO_EMPTY_THRHD  ((0x1FF)<<(9))
//used to get addr of flag in order to write 
#define EMPTY_THR_OFFSET 0x9

#define UART_CLK_CONF_REG(i)   (C3_UART(i) + 0x78)
/*description: Set this bit to enable UART Rx clock.*/
#define UART_RX_SCLK_EN  (BIT(25))
/*description: Set this bit to enable UART Tx clock.*/
#define UART_TX_SCLK_EN  (BIT(24))
/*description: Write 1 then write 0 to this bit  reset UART Tx/Rx.*/
#define UART_RST_CORE  (BIT(23))
#define RST_CORE_OFFSET 23
/*description: Set this bit to enable UART Tx/Rx clock.*/
#define UART_SCLK_EN  (BIT(22))
#define SCLK_EN_OFFSET 22
/*description: UART clock source select. APB_CLK; 2: RC_FAST_CLK; 3: XTAL_CLK*/
#define UART_SCLK_SEL ((0x3)<<(20))
#define SCLK_SEL_OFFSET 20
/*description: The integral part of the frequency divider factor.*/
#define UART_SCLK_DIV_NUM  ((0xFF)<<(12))
/*description: The numerator of the frequency divider factor.*/
#define UART_SCLK_DIV_A  ((0x3F)<<(6))
/*description: The  denominator of the frequency divider factor.*/
#define UART_SCLK_DIV_B  0x0000003F

static inline void uart_set_mem_clk(UART_t i, UART_state n)
{
    REG_WRITE((UART_CONF0_REG(i) + MEM_CLK_EN_OFFSET), n);   
}

static inline void uart_reset_core(UART_t i, UART_state n)
{
    REG_WRITE((UART_CLK_CONF_REG(i) + RST_CORE_OFFSET), n);
}

static inline void uart_set_clk_source(UART_t i, soc_periph_uart_clk_src_legacy_t n)
{
    REG_WRITE((UART_CLK_CONF_REG(i) + SCLK_SEL_OFFSET), n);
}

static inline void uart_enable_clock(UART_t i, UART_state n)
{
    REG_WRITE((UART_CLK_CONF_REG(i) + SCLK_EN_OFFSET), n);
}

/*
 * divider = clk_hz
 * integral part = floor(divider)
 * frag part = round((divider - integral part) * 16 )
 */
static inline void uart_set_baudrate(UART_t i, uint32_t clk_hz, uint32_t baud)
{
    double div = (double)clk_hz / (double)baud;
    uint32_t div_int = (uint32_t)div; //floors div (type cast rounds down)
    uint32_t div_frag = (uint32_t)((div - div_int) * 16.0 + 0.5);  //rounds by type cast the num +0.5

    if(div_frag > 15){
        div_frag = 0;
        div_int += 1;
    }

    // UART_CLKDIV_FRAG [23:20] and UART_CLKDIV [11:0] reste is reserved (0)
    // Contains only divider fields, the entire UART_CLKDIV_REG register is overwritten 
    uint32_t reg =
        ((div_int  & UART_CLKDIV) << CLKDIV_OFFSET) |
        ((div_frag & UART_CLKDIV_FRAG) << CLKDIV_FRAG_OFFSET);

    REG_WRITE(UART_CLKDIV_REG(i), reg);
}


static inline void set_txfifo_empty_thr(UART_port i, uint16_t thr_val)
{
    REG_WRITE((UART_CONF1_REG(i) + EMPTY_THR_OFFSET), thr_val);
}

/*will return 1 if tx fifo is not full*/
static inline bool txfifo_status(UART_port i)
{
    return (bool)(READ_REG(UART_INT_RAW_REG(i)) & UART_TXFIFO_EMPTY_INT_RAW);
}


// Read the data byte in uart FIFO register
static inline uint8_t uart_read_byte(UART_port i)
{
    return (uint8_t)(READ_REG(UART_FIFO_REG(i)) & UART_RXFIFO_RD_BYTE);
}

// Write data byte to uart FIFO register
static inline void uart_write_byte(UART_port i, uint8_t b)
{
    if(txfifo_status(i)){
        REG_WRITE(UART_FIFO_REG(i), b);
    }
}





