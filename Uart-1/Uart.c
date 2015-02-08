
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

#define AUX_ENABLES     0x20215004
#define AUX_MU_IO_REG   0x20215040
#define AUX_MU_IER_REG  0x20215044
#define AUX_MU_IIR_REG  0x20215048
#define AUX_MU_LCR_REG  0x2021504C
#define AUX_MU_MCR_REG  0x20215050
#define AUX_MU_LSR_REG  0x20215054
#define AUX_MU_MSR_REG  0x20215058
#define AUX_MU_SCRATCH  0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068


extern void NOP ();
extern unsigned int GET32 (unsigned int);
extern void PUT32 (unsigned int, unsigned int);

void uart_init();
void uart_putc(unsigned int);

void k_main()
{
    //Set up LED indicator

    unsigned int pin16_bits = GET32(GPIO_FUNCSEL_1);
    pin16_bits &= ~(7<<18);  //clears the 3 bits controlling GPIO pin 16 (6x3 = 18)
    pin16_bits |= 1<<18;     //Enables GPIO pin 16 for output
    PUT32(GPIO_FUNCSEL_1, pin16_bits);

    //Let there the light! - Transmitting
    PUT32(GPIO_CLR_0, 1<<16);

    uart_init();
    while(TRUE)
    {
        for(int i = 0; i<26; i++)
        {
            uart_putc(97+i);
        }
    }
}

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
