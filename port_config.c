#include <inttypes.h>
#include <stdlib.h>

#define CPU_CLOCK_HZ 100000000  // 100MHZ
#define TICK_RATE_HZ 1000       // 1ms tick
#define CMPADDR 0x00000000800800cc //tmp addr value pulled from demo .map, would need code to find the real addr

// initialise variables/registers for timer interupt
volatile uint64_t ullNextTime = 0ULL;
const uint64_t* pullNextTime = &ullNextTime; 
volatile const size_t uxTimerIncrementsForOneTick = (size_t) ((CPU_CLOCK_HZ) / (TICK_RATE_HZ)); //initial clock tick value
volatile uint64_t* pullMachineTimerCompareRegister = CMPADDR; // addr of hardware timer cmp register


