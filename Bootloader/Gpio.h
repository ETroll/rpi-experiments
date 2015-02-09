#ifndef GPIO_H
#define GPIO_H

#define TRUE  1
#define FALSE 0

#define SIZE_WORD  4
#define SIZE_HWORD 2

#define BCM2708_PERIF_BASE  0x20000000
#define GPIO_CTRL_BASE      (BCM2708_PERIF_BASE + 0x200000)

#define GPIO_FUNCSEL_0      GPIO_CTRL_BASE
#define GPIO_FUNCSEL_1      (GPIO_FUNCSEL_0 + SIZE_WORD)

#define GPIO_SET_0          (GPIO_CTRL_BASE + 0x1C)
#define GPIO_SET_1          (GPIO_SET_0 + SIZE_WORD)
#define GPIO_CLR_0          (GPIO_CTRL_BASE + 0x28)
#define GPIO_CLR_1          (GPIO_CLR_0 + SIZE_WORD)

//GPIO Pin Pull-up/down Enable
#define GPIO_PUD            (GPIO_CTRL_BASE + 0x94)
#define GPIO_PUD_CLK0       (GPIO_CTRL_BASE + 0x98)
#define GPIO_PUD_CLK1       (GPIO_CTRL_BASE + 0x9C)


//TODO: Separate these external declarations out of the GPIO header?
extern void NOP ();
extern unsigned int GET32 (unsigned int);
extern void PUT32 (unsigned int, unsigned int);
extern void BRANCHTO (unsigned int);

#endif
