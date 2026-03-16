/*DATE & TIME*/
#include"header.h"
extern char h,m,s;
extern char d,mn,y;
void time_data(void)
{
unsigned char AmPm=' ';
        /*time */
        //h=i2c_receive(0xD0,0x02); //24hrs
				h=i2c_receive(0xD0,0x02);
			
			////AM/PM
				if(h&(1<<6))
				{
					if(h&(1<<5))
					{
						AmPm='P';
						//lcd_string("PM");
						//uart0_tx_string("PM");
					}
					else
					{
						AmPm='A';
						//lcd_string("AM");
						//uart0_tx_string("AM");
					}
					h=h&0x1F;
				}
			
        m=i2c_receive(0xD0,0x01);
        s=i2c_receive(0xD0,0x00);

        /*display time in lcd*/
        lcd_cmd(0x80);
        lcd_data((h/16)+48);
        lcd_data((h%16)+48);
        lcd_data(':');
        lcd_data((m/16)+48);
        lcd_data((m % 16)+48);
        lcd_data(':');
        lcd_data((s/16)+48);
        lcd_data((s%16)+48);

        /*display time in uart*/
        uart0_tx((h/16)+48);
        uart0_tx((h%16)+48);
        uart0_tx(':');
        uart0_tx((m/16)+48);
        uart0_tx((m%16)+48);
        uart0_tx(':');
        uart0_tx((s/16)+48);
        uart0_tx((s%16)+48);
				
				if(AmPm=='A')
				{
					lcd_string("AM");
					uart0_tx_string(" AM");
				}
					
				
				else if(AmPm=='P')
				{	
				lcd_string("PM");
				uart0_tx_string(" PM");
				}
			
				uart0_tx(' ');
				lcd_string("");
        /*date*/
        d=i2c_receive(0xD0,0x04);
        mn=i2c_receive(0xD0,0x05);
        y=i2c_receive(0xD0,0x06);

        /*prrint date on Lcd 
        lcd_cmd(0xC0);
        lcd_data((d/16)+48);
        lcd_data((d%16)+48);
        lcd_data('/');
        lcd_data((mn/16)+48);
        lcd_data((mn%16)+48);
        lcd_data('/');
        lcd_data((y/16)+48);
        lcd_data((y%16)+48);*/

        /* date print in uart */
        uart0_tx((d/16)+48);
        uart0_tx((d%16)+48);
        uart0_tx('/');
        uart0_tx((mn/16)+48);
        uart0_tx((mn%16)+48);
        uart0_tx('/');
        uart0_tx((y/16)+48);
        uart0_tx((y%16)+48);
				
				
}


