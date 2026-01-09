#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg.h"


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

static inline void uart_init();

// Read the data byte in uart FIFO register
static inline uint8_t uart_read_byte(UART_port i)
{
    return (uint8_t)(READ_REG(UART_FIFO_REG(i)) & UART_RXFIFO_RD_BYTE);
}

// Write data byte to uart FIFO register
static inline void uart_write_byte(UART_port i, uint8_t b)
{
    REG_WRITE(UART_FIFO_REG(i), b);
}