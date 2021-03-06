
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define GPIOEBASE 0x40021000
#define RCCBASE 0x40023800

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018
#define STK_MASK 0x00FFFFFF

#define DELAYVALUE 32

static int delay ( unsigned int n )
{
    unsigned int ra;

    while(n--)
    {
        while(1)
        {
            ra=GET32(STK_CSR);
            if(ra&(1<<16)) break;
        }
    }
    return(0);
}

int notmain ( void )
{
    unsigned int ra;
    unsigned int rx;


    ra=GET32(RCCBASE+0x30);
    ra|=1<<4; //enable port e
    PUT32(RCCBASE+0x30,ra);

    //moder
    ra=GET32(GPIOEBASE+0x00);
    ra&=~(3<<(0<<1));
    ra|= (1<<(0<<1));
    PUT32(GPIOEBASE+0x00,ra);
    //OTYPER
    ra=GET32(GPIOEBASE+0x04);
    ra&=~(1<<0);
    PUT32(GPIOEBASE+0x04,ra);

    PUT32(STK_CSR,4);
    PUT32(STK_RVR,1000000-1);
    PUT32(STK_CVR,0x00000000);
    PUT32(STK_CSR,5);

    for(rx=0;;rx++)
    {
        PUT32(GPIOEBASE+0x18, (1<<(0+ 0)) );
        delay(DELAYVALUE);
        PUT32(GPIOEBASE+0x18, (1<<(0+16)) );
        delay(DELAYVALUE);
    }
    return(0);
}

/*
dfu-util -a 0 -s 0x08000000 -D blinker02.bin
*/

