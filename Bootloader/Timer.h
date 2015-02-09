#ifndef TIMER_H
#define TIMER_H

#define ARM_TIMER_CTL 0x2000B408
#define ARM_TIMER_CNT 0x2000B420

void timer_init();
unsigned int timer_tick();

#endif
