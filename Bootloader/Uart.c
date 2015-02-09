#include "Uart.h"
#include "Gpio.h"


void uart_init()
{
    unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270); //115200 baud

    ra = GET32(GPIO_FUNCSEL_1);
    ra &= ~(7<<12); //gpio14
    ra |= 2<<12;    //alt5
    ra &= ~(7<<15); //gpio15
    ra |= 2<<15;    //alt5

    PUT32(GPIO_FUNCSEL_1,ra);
    PUT32(GPIO_PUD,0);

    for(int i=0; i<150; i++)
    {
        NOP();
    }

    PUT32(GPIO_PUD_CLK0, (1<<14)|(1<<15));

    for(int i=0; i<150; i++)
    {
        NOP();
    }
    PUT32(GPIO_PUD_CLK0,0);
    PUT32(AUX_MU_CNTL_REG,3);
}

unsigned int uart_check(void)
{
    if(GET32(AUX_MU_LSR_REG) & 0x01)
    {
        return(1);
    }
    return(0);
}

void uart_putc(unsigned int c)
{
    while(TRUE)
    {
        if(GET32(AUX_MU_LSR_REG)&0x20)
        {
            break;
        }
    }
    PUT32(AUX_MU_IO_REG, c);
}

unsigned int uart_getc(void)
{
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG) & 0x01)
        {
            break;
        }
    }
    return(GET32(AUX_MU_IO_REG) & 0xFF);
}

void uart_writeline(const char* data)
{
    unsigned int i = 0;
    while (data[i] != '\0')
    {
        uart_putc(data[i++]);
    }
    uart_putc(0x0D);
    uart_putc(0x0A);
}
