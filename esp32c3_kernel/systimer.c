#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "periph.h"

/**
 * @brief systimer's clock source is fixed to XTAL (40MHz), and has a fixed fractional divider (2.5).
 *        So the resolution of the systimer is 40MHz/2.5 = 16MHz.
 */

uint64_t systimer_ticks_to_us(uint64_t ticks)
{
    return ticks / 16;
}

uint64_t systimer_us_to_ticks(uint64_t us)
{
    return us * 16;
}

uint64_t systimer_get_time(void)
{
    return systimer_ticks_to_us(systimer_now());
}

void delay_us(uint64_t us) 
{
    uint64_t until = systimer_now() + us;
    while (systimer_now() < until) spin(1);
}





