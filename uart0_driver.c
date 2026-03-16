#include "header.h"
#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
int pclk,result;
unsigned int a[]={15,60,30,15,0};
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0 |=0x5;
U0LCR=0x83;
//U0DLL=98;  //for lower byte
//U0DLM=0;
U0DLL=result&0xff;  //for lower byte
U0DLM=(result>>8)&0xff; //for 2nd byte(higher byte) check
U0LCR=0x03;
}

#define THRE (U0LSR>>5&1)          
void uart0_tx(unsigned int data)
{
while(THRE==0);
U0THR=data;
//while(THRE==0);
}

//receiver
#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}
//to print string like printf() function
void uart0_tx_string(unsigned char *p)
{
        while(*p!=0)
        {
        uart0_tx(*p++);
        //p++;
        }
}

//ascii to int only 1byte
int uart0_integer(const char *p)
{
        unsigned int k=1,num=0;
        if(*p=='-')
        {      
								k=-k;
                p++;
        }
        if(*p=='+')
        {
        k=1;
        p++;
        }
        while(*p)
        {
        if(*p>='0' &&*p<='9')
        {
                num=num*10+(*p-48);
        }
        else
        break;
        p++;
        }
				
				
//      while(uart0_rx()!=0);
//uart0_tx(m);
        return num*k;
}

//to print numbers
void uart0_printnum(int n)
{
	char b[10];
	int i=0;
	if(n==0)
	{
		uart0_tx('0');
		return;
	}
	if(n<0)
	{
		uart0_tx('-');
		n=-n;
	}
	while(n>0)
	{
		b[i]=(n%10)+48;
		n=n/10;
		i++;
	}
	while(i)
	{
		--i;
		uart0_tx(b[i]);
 	}
}

//rx string
void uart0_rx_string(char *p,unsigned int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		while(RDR==0);
		p[i]=U0RBR;
		uart0_tx(p[i]);       //print in serial terminal  (loop back
				//uart0_tx('*');   //for password authentication  shows ****
		if(p[i]=='\r'||p[i]=='\n')
			break;
	}
	p[i]='\0';
}
//float num
float	uart0_rx_float()
{
	int n1,n2=0,i=0,k=1,d=1;
	float res;
	
	char s[10];
	uart0_rx_string( s,10);
	if(s[0]=='-')
	{
		k=-1;
		i++;
	}
	else if(s[0]=='+')
    i++;
	for(n1=0;s[i] &&s[i]!='.';i++)
	{
		n1=n1*10+(s[i]-48);
	}
	
if(s[i]=='.')
i++;	
	for(;s[i];i++)
		{
			n2=n2*10+(s[i]-48);
			d=d*10;
			
		}
	
		res=n1+((float)n2/d);
	return res*k;
}
/*
//float printing on tx
void uart0_tx_float(float f)
{
	int n;
	if(f<0)
	{
		uart0_tx('-');
		f=-f;
	}
	if(f==0)
	{
		uart0_tx_string("0.0");
		return;
	}
	n=f;
	uart0_printnum(n);
	uart0_tx('.');
	n=(f-n)*100;
	uart0_printnum(n);
}
*/
//hexa
void uart0_hexa(unsigned int num)
{
	char hex[]="0123456789ABCDEF";
	for(int i=28;i>=0;i=i-4)
		uart0_tx(hex[(num>>i)&0xF]);
}

//float tx
void uart0_tx_float(float f)
{
    int num,frac;

    if (f<0) {
        uart0_tx('-');
        f=-f;
    }

    num=(int)f;                     // integer part
    frac=(int)((f-num)*100);  // 2 decimal places
		//frac = (int)((f * 100) + 0.5) % 100; 

    if (frac < 0) 
        frac = -frac;

    uart0_printnum(num);
    uart0_tx('.');

   /* if(frac<100) 
			uart0_tx('0');
    if(frac<10)  
			uart0_tx('0');
*/
    uart0_printnum(frac);
}


