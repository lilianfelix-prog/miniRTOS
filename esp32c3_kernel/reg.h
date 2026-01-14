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
#define REG_SET_BIT(x, a) (*(volatile uint32_t *) (x) |= (a))
#define REG_CLR_BIT(x, a) (*(volatile uint32_t *)(x) &= ~(a))

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
    ENABLE
} UART_state;

typedef enum {
    UART_DATA_5_BITS   = 0x0,    /*!< word length: 5bits*/
    UART_DATA_6_BITS   = 0x1,    /*!< word length: 6bits*/
    UART_DATA_7_BITS   = 0x2,    /*!< word length: 7bits*/
    UART_DATA_8_BITS   = 0x3,    /*!< word length: 8bits*/
    UART_DATA_BITS_MAX = 0x4,
} uart_word_length_t;

typedef enum {
    UART_STOP_BITS_1   = 0x1,  /*!< stop bit: 1bit*/
    UART_STOP_BITS_1_5 = 0x2,  /*!< stop bit: 1.5bits*/
    UART_STOP_BITS_2   = 0x3,  /*!< stop bit: 2bits*/
    UART_STOP_BITS_MAX = 0x4,
} uart_stop_bits_t;

typedef enum {
    UART_PARITY_DISABLE  = 0x0,  /*!< Disable UART parity*/
    UART_PARITY_EVEN     = 0x2,  /*!< Enable UART even parity*/
    UART_PARITY_ODD      = 0x3   /*!< Enable UART odd parity*/
} uart_parity_t;

#define UART0_TX_SIGNAL  6
#define UART0_RX_SIGNAL  7

#define TX_FIFO_SIZE 128
// The addresses in this section are relative to UART Controller base address provided
/*
 * How the register bit mask works:
 * UART_FIFO_REG & UART_REG_FLAG_MASK = (flag's register region according to specs)
 */

//enable UART clock.
#define SYSTEM_PERIP_CLK_EN0_REG (C3_SYSTEM + 0x10)
#define SYSTEM_UART_CLK_EN (BIT(2))


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
// enable UART RAM clock gating
#define UART_MEM_CLK_EN  (BIT(28))
#define MEM_CLK_EN_OFFSET 28

// force clock on register
#define UART_CLK_EN (BIT(25))

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

#define UART_STATUS_REG(i)  (C3_UART(i) + 0x1c)
#define UART_TXFIFO_CNT ((0x3FF)<<(16))

#define UART_CONF1_REG(i)  (C3_UART(i) + 0x24)
/*interupt when receiver data > this val*/
#define UART_RXFIFO_FULL_THRHD   ((0x1FF)(0))
#define FULL_THR_OFFSET 0x0
/*interupt when tx fifo is less then this val*/
#define UART_TXFIFO_EMPTY_THRHD  ((0x1FF)<<(9))
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

// Enables periph clock (APB, bus clock)
static inline void uart_set_periph_clk(UART_state n)
{
    if(n == DISABLE){
        REG_CLR_BIT(SYSTEM_PERIP_CLK_EN0_REG, SYSTEM_UART_CLK_EN);  
    } else {
        REG_SET_BIT(SYSTEM_PERIP_CLK_EN0_REG, SYSTEM_UART_CLK_EN);
    }
}

static inline void uart_set_fifo_clk(UART_port i)
{
    REG_SET_BIT(UART_CONF0_REG(i), UART_MEM_CLK_EN);   
}

//TODO: read register once 
static inline void uart_rst_tx_fifo(UART_port i)
{
    REG_CLR_BIT(UART_CONF0_REG(i), UART_TXFIFO_RST);
    REG_SET_BIT(UART_CONF0_REG(i), UART_TXFIFO_RST);
}

static inline void uart_rst_rx_fifo(UART_port i)
{
    REG_CLR_BIT(UART_CONF0_REG(i), UART_RXFIFO_RST);
    REG_SET_BIT(UART_CONF0_REG(i), UART_RXFIFO_RST);
}

static inline void uart_set_data_bits(UART_port i, uart_word_length_t n)
{
    REG_CLR_BIT(UART_CONF0_REG(i), UART_BIT_NUM);
    REG_SET_BIT(UART_CONF0_REG(i), ((n << BIT_NUM_OFFSET) & UART_BIT_NUM));
}

static inline void uart_enable_flow_control(UART_port i, UART_state n)
{
    if(n == DISABLE){
        REG_CLR_BIT(UART_CONF0_REG(i), UART_CLK_EN);  
    } else {
        REG_SET_BIT(UART_CONF0_REG(i), UART_CLK_EN);
    }
}

static inline void uart_set_clk_on(UART_port i, UART_state n)
{
    if(n == DISABLE){
        REG_CLR_BIT(UART_CONF0_REG(i), UART_TX_FLOW_EN);  
    } else {
        REG_SET_BIT(UART_CONF0_REG(i), UART_TX_FLOW_EN);
    }
}

static inline void uart_set_stop_bit(UART_port i, uart_stop_bits_t n)
{
    REG_CLR_BIT(UART_CONF0_REG(i), UART_STOP_BIT_NUM);
    REG_SET_BIT(UART_CONF0_REG(i), ((n << STOP_BIT_OFFSET) & UART_STOP_BIT_NUM));
}

static inline void uart_set_parity(UART_port i, uart_parity_t n)
{
    REG_CLR_BIT(UART_CONF0_REG(i), UART_PARITY);
    REG_SET_BIT(UART_CONF0_REG(i), ((n << PARITY_OFFSET) & UART_PARITY));
}

static inline void uart_reset_core(UART_port i)
{
    REG_SET_BIT(UART_CLK_CONF_REG(i), UART_RST_CORE);
    REG_CLR_BIT(UART_CLK_CONF_REG(i), UART_RST_CORE);
}

static inline void uart_set_clk_source(UART_port i, soc_periph_uart_clk_src_legacy_t n)
{
    REG_CLR_BIT(UART_CLK_CONF_REG(i), UART_SCLK_SEL);
    REG_SET_BIT(UART_CLK_CONF_REG(i), ((n << SCLK_SEL_OFFSET) & UART_SCLK_SEL));
}

static inline void uart_set_clock(UART_port i, UART_state n)
{
    if(n == ENABLE){
        REG_SET_BIT(UART_CLK_CONF_REG(i), UART_SCLK_EN);
    } else {
        REG_CLR_BIT(UART_CLK_CONF_REG(i), UART_SCLK_EN);
    }
}

/*
 * divider = clk_hz
 * integral part = floor(divider)
 * frag part = round((divider - integral part) * 16 )
 */
static inline void uart_set_baudrate(UART_port i, uint32_t clk_hz, uint32_t baud)
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
    REG_CLR_BIT(UART_CONF1_REG(i), UART_TXFIFO_EMPTY_THRHD);
    REG_SET_BIT(UART_CONF1_REG(i), ((thr_val << EMPTY_THR_OFFSET) & UART_TXFIFO_EMPTY_THRHD));
}

/*will return 0 if tx fifo is full*/
static inline bool txfifo_has_space(UART_port i)
{
    return ((READ_REG(UART_STATUS_REG(i)) & UART_TXFIFO_CNT) < TX_FIFO_SIZE);
}


/* ----- GPIO ----- */

typedef enum 
{
    GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7,
    GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14,
    GPIO15, GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21
} GPIO_pin;

// enable read/write of the gpio
typedef enum
{
    R,
    W,
    R_W
} GPIO_state;

// The values of bit 0 ~ bit 21 correspond to the output value of GPIO0 ~ GPIO21 respectively
#define GPIO_OUT_REG (C3_GPIO + 0x04)
#define GPIO_OUT_DATA_ORIG (BIT(0))

#define GPIO_OUT_W1TS_REG (C3_GPIO + 0x08)

#define GPIO_OUT_W1TC_REG (C3_GPIO + 0x0c)

//write 1 to set GPIO_ENABLE_REG
#define GPIO_ENABLE_W1TS_REG (C3_GPIO + 0x24)

//write 1 to clear GPIO_ENABLE_REG
#define GPIO_ENABLE_W1TC_REG (C3_GPIO + 0x28)

#define GPIO_FUNC_OUT_SEL_CFG_REG(i) (C3_GPIO + (0x554 + (4*i)))
/* 
 * Selection control for GPIO output n. If a value Y (0<=Y<128) is written to this
 * field, the peripheral output signal Y will be connected to GPIO output n 
 */
#define GPIO_FUNC_OUT_SEL(i) (BIT(0))

#define GPIO_ENABLE_REG (C3_GPIO + 0x20)
/* GPIO output enable register for GPIO0 ~ 21. Bit0 ~ bit21 are corresponding to
GPIO0 ~ 21 */
#define GPIO_ENABLE_DATA (BIT(0))

#define GPIO_IN_REG (C3_GPIO + 0x3c)
// holds the input values signal of each GPIO pin 0 ~ 21
#define GPIO_IN_DATA_NEXT (BIT(0))

#define IO_MUX_GPIO_REG(i) (C3_IO_MUX + (0x04 + (4*i))) 
// Input enable of the pin during sleep mode (necessary to enable for input)
#define IO_MUX_GPIO_MCU_IE (BIT(4))
#define MCU_IE_OFFSET 4

/*
 * Configure GPIO matrix --> IO MUX and then to a pin 
 * pin 0 ~ 21
 */
static inline void gpio_enable_pin(GPIO_pin pin, GPIO_state state)
{
    if(state == W || state == R_W){
        // enable corresponding GPIO pin x 
        // register is atomic, only react to 1s
        REG_WRITE(GPIO_ENABLE_W1TS_REG, BIT(pin));

        // route UART0 TX to this GPIO
        REG_WRITE(GPIO_FUNC_OUT_SEL_CFG_REG(pin), UART0_TX_SIGNAL);
    }

    if(state == R || state == R_W){
        // enable the input via IO MUX
        REG_SET_BIT(IO_MUX_GPIO_REG(pin), IO_MUX_GPIO_MCU_IE);
    }

}