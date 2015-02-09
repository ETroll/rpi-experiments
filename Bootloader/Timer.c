#include "Timer.h"
#include "Gpio.h"


void timer_init(void)
{
    //0xF9+1 = 250
    //250MHz/250 = 1MHz
    PUT32(ARM_TIMER_CTL,0x00F90000);
    PUT32(ARM_TIMER_CTL,0x00F90200);
}

unsigned int timer_tick(void)
{
    return(GET32(ARM_TIMER_CNT));
}
