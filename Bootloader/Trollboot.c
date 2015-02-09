
#include "Gpio.h"
#include "Uart.h"
#include "Timer.h"

#define ARMBASE 0x8000

#define SOH 0x01
#define ACK 0x06
#define NAK 0x15
#define EOT 0x04
#define CAN 0x18

//NOTICE: Timer set at 1 million ticks per second
#define NAKSOH_TIMEOUT 4000000
#define WAIT_AFTER_EOT_TIMEOUT 2000000
#define WAIT_AFTER_CAN_TIMEOUT 2000000

//TODO: Add simple commandlist

void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_putc(rc);
        if(rb==0) break;
    }
    uart_putc(0x20);
}

void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_putc(0x0D);
    uart_putc(0x0A);
}

void bootloader()
{
    unsigned int pin16_funcbits = GET32(GPIO_FUNCSEL_1);
    pin16_funcbits &= ~(7<<18);
    pin16_funcbits |= 1<<18;

    PUT32(GPIO_FUNCSEL_1, pin16_funcbits);
    PUT32(GPIO_CLR_0, 1<<16);

    uart_init();
    timer_init();
    uart_writeline("Trollboot - Ready for your program!");



    while(TRUE)
    {
        unsigned int start = timer_tick();
        unsigned int state = 192;
        unsigned int checksum = 0;
        unsigned int block = 1;
        unsigned int bytesRecieved = 0;
        unsigned char* xstring = (unsigned char*)ARMBASE;

        uart_putc(NAK);
        while(TRUE)
        {
            unsigned int current = timer_tick();

            if((current-start) >= NAKSOH_TIMEOUT)
            {
                uart_putc(NAK);
                start = current;
            }
            if(uart_check())
            {
                break;
            }
        }

        //We have a program beeing sent over. Lets get it!
        while(state != 255)
        {
            unsigned int data = uart_getc();

            switch(state)
            {
                case 192:
                {
                    switch(data)
                    {
                        //Start transfering data
                        case SOH:
                        {
                            checksum = data;
                            state++;
                            break;
                        }

                        //Finnished transfering data
                        case EOT:
                        {
                            uart_putc(ACK);
                            start = timer_tick();
                            while(TRUE)
                            {
                                unsigned int current = timer_tick();
                                if((current-start) >= WAIT_AFTER_EOT_TIMEOUT)
                                {
                                    break;
                                }
                            }



                            uart_writeline("Bytes recieved:");
                            hexstring(bytesRecieved);
                            uart_writeline("xstring:");
                            hexstring((unsigned int)xstring);
                            uart_writeline("Ready to run. Press g/G to run.\0");

                            //xstring[bytesRecieved++] = 

                            while(TRUE)
                            {
                                data = uart_getc();
                                if((data == 'g') || (data == 'G'))
                                {
                                    uart_writeline("Branching to program. Good bye!\0");
                                    BRANCHTO(ARMBASE);
                                }
                            }
                            break;
                        }
                        default:
                        {
                            state = 255;
                            break;
                        }
                    }
                    break;
                }
                case 193:
                {
                    if(data == block)
                    {
                        checksum += data;
                        state++;
                    }
                    else
                    {
                        state = 255;
                    }
                    break;
                }
                case 194:
                {
                    if(data == (0xFF-block))
                    {
                        checksum += data;
                        state = 0;
                    }
                    else
                    {
                        state = 255;
                    }
                    break;
                }
                case 128:
                {
                    checksum &= 0xFF;
                    if(data == checksum)
                    {
                        uart_putc(ACK);
                        block = (block+1) & 0xFF;
                        xstring += 128;
                        state = 192;
                    }
                    else
                    {
                        state = 255;
                    }
                    break;
                }
                default:
                {
                    checksum += data;
                    xstring[state] = data & 0xFF;
                    state++;
                    bytesRecieved++;
                    break;
                }
            }
        }
    }




}
