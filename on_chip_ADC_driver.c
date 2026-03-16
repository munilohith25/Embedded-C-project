#include <lpc21xx.h>
#include "header.h"

/* sensor temp + pot */
#define AD0CR   (*((volatile unsigned int *)0xE0034000))
#define AD0GDR  (*((volatile unsigned int *)0xE0034004))


void adc_init(void)
{
    PINSEL1 |=(1<<24);   // P0.28=AD0.1
    PINSEL1 |=(1<<26);   // P0.29=AD0.2

    AD0CR = (1<<21)|(4<<8); // ADC ON, clk div
}

unsigned int adc_read(unsigned int ch)
{
    unsigned int res;
    AD0CR &= ~(0xFF);     
		AD0CR |= (1<<ch);       // select channel

    AD0CR &= ~(7<<24);      // clear START
    AD0CR |=  (1<<24);      // start ADC

    while((AD0GDR&(1<<31))==0); // wait DONE

    res=(AD0GDR>>6)&0x3FF;
    return res;
}
