#include<lpc21xx.h>
#include "header.h"
#define RS (1<<17)   //p1.17
#define RW (1<<18)   //p1.18
#define EN (1<<19)   //p1.19
void lcd_data(unsigned char data)
{
//higher nibble
unsigned int temp;
IOCLR1=0xFE<<16;         //p1->17,18,19,20,21,22,23
temp=(data&0xF0)<<16;
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
//delay_ms(500);
//lower nibble
IOCLR1=0xFE<<16;
temp=((data&0x0F)<<20);
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;

//delay_ms(500);
}
void lcd_cmd(unsigned int cmd)
{
//higher nibble
unsigned int temp;
IOCLR1=0xFE<<16;
temp=((cmd&0xF0)<<16);
IOSET1=temp;
IOCLR1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;

//lower nibble
IOCLR1=0xFE<<16;
temp=((cmd&0x0F)<<20);
IOSET1=temp;
IOCLR1=RS;	//RS=0->cmd mode
IOCLR1=RW;  //RW=0->write
IOSET1=EN;	//EN=1 set
delay_ms(2);
IOCLR1=EN;	//EN=1 clear
}

void lcd_init()
{
IODIR1=0xFE<<16;
lcd_cmd(0x02);
lcd_cmd(0x03);
lcd_cmd(0x28);
lcd_cmd(0x0E);
lcd_cmd(0x01);
}

void lcd_string(char *p)
{
        while(*p)
            lcd_data(*p++);
}
//integer func
void lcd_integer(int num)
{
	//char a[10];
	char a[3];
	/*2 digit*/
	  if(num>99) //
        num=99;
		
	int i=0;
	if(num==0)
	{
		lcd_data('0');
		return;
	}
	while(num)
	{
		a[i]=(num%10)+48; //ascii add
		num=num/10;
		i++;
	}
	i--;
	while(i>=0)
	{
		lcd_data(a[i]);
		i--;
	}
}

//float func
void lcd_float(double f)
{
	int num;
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}
	if(f==0)
	{
		lcd_string("0.0");
		return;
	}
	num=f; 
	lcd_integer(num);
	lcd_data('.');
	num=(f-num)*100+0.5;	//multiply float
	//num=	(int)((f * 100) + 0.5) % 100;

	/*if(num<100)
	lcd_data('0');

if(num<10)
	lcd_data('0');*/
	lcd_integer(num);
	
}

void lcd_cgram(void)
{
	/*
unsigned char a[]={
	0x17,0x14,0x14,0x1f,0x05,0x05,0x1D,0x00,
	0x0e,0x1f,0x11,0x11,0x11,0x11,0x1f,0x00,
	0x0e,0x1f,0x11,0x11,0x11,0x1f,0x1f,0x00,
};*/
	 unsigned char a[] =
    {
			/*light symbol page0*/
         0x0E,0x1F,0x1F,0x1F,0x0E,0x04,0x0E,0x04 ,
        /*degree symbol page1 */
        0x06,0x09,0x09,0x06,0x00,0x00,0x00,0x00
		};
	
int i;
lcd_cmd(0x40);  //starting addr of cgram
for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
lcd_data(a[i]);

}





