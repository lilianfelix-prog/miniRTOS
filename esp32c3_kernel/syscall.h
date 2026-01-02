#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT(x) ((uint32_t) 1U << (x))
#define REG(x) ((volatile uint32_t *) (x))

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
#define C3_UART 0x60000000
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


// Machine Status Register, mstatus
#define MSTATUS_MPP_MASK (3 << 11) // previous mode.
#define MSTATUS_MPP_M (3 << 11)
#define MSTATUS_MPP_S (1 << 11)
#define MSTATUS_MPP_U (0 << 11)
#define MSTATUS_MIE (1 << 3)    // machine-mode interrupt enable.

// ESP32-C3 is single-hart so always return 0
static inline uint32_t r_mhartid()
{
    uint32_t x;
    asm volatile("csrr %0, mhartid" : "=r" (x) );
    return x;
}


static inline uint32_t r_mstatus()
{
    uint32_t x;
    asm volatile("csrr %0, mstatus" : "=r" (x) );
    return x;
}

static inline void w_mstatus(uint32_t x)
{
    asm volatile("csrw mstatus, %0" : : "r" (x));
}

static inline void w_mepc(uint32_t x)
{
    asm volatile("csrw mepc, %0" : : "r" (x));
}

static inline uint32_t r_mepc()
{
    uint32_t x;
    asm volatile("csrr %0, mepc" : "=r" (x));
    return x;
}

// Machine Scratch register, for early trap handler
static inline void w_mscratch(uint32_t x)
{
    asm volatile("csrw mscratch, %0" : : "r" (x));
}

// Machine-mode interrupt vector
static inline void w_mtvec(uint32_t x)
{
    asm volatile("csrw mtvec, %0" : : "r" (x));
}

// Machine-mode Interrupt Enable
#define MIE_MEIE (1 << 11) // external
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // software

static inline uint32_t r_mie()
{
    uint32_t x;
    asm volatile("csrr %0, mie" : "=r" (x) );
    return x;
}

static inline void w_mie(uint32_t x)
{
    asm volatile("csrw mie, %0" : : "r" (x));
}

/*
 * Find the clock source, there is a clock source bit 
 * in the SYSTIMER register:
 * 0 -> XTAL
 * 1 -> APB
 */
#define SYSTIMER_CONF_CLK_SEL BIT(1)

static inline bool systimer_uses_xtal(void)
{
    return !(REG(C3_SYSTIMER)[0] & SYSTIMER_CONF_CLK_SEL);
}


static inline void spin(volatile uint64_t count) 
{
  while (count--) asm volatile("nop");
}


static inline uint64_t systimer_now()
{
    uint32_t lo, lo_start, hi;
    
    /* Read LO, HI, then LO again, check that LO returns the same value.
     * This accounts for the case when an interrupt may happen between reading
     * HI and LO values, and this function may get called from the ISR.
     * In this case, the repeated read will return consistent values.
     * HI = base + 16 * 4 = base + 0x40
     * LO = base + 17 * 4 = base + 0x44
     */
    lo_start = REG(C3_SYSTIMER)[17];
    do {
        lo = lo_start;
        hi = REG(C3_SYSTIMER)[16];
        lo_start = REG(C3_SYSTIMER)[17];
    } while (lo_start != lo);

    return ((uint64_t)hi << 32) | lo;
}

#define SYSTIMER_FREQ_HZ 16000000ULL

uint64_t systimer_ticks_to_us(uint64_t ticks);
uint64_t systimer_us_to_ticks(uint64_t us);
uint64_t systimer_get_time(void);
