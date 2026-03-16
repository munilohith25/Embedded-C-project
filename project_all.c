/* main.c */
/* uart driver + spi + i2c + mcp + lcd 4bit + delay */
char h,m,s;
char d,mn,y;
#include "header.h"
int main(void)
{
    //char day;
    unsigned int light;
    unsigned int ch0,ch1,ch2;
    unsigned int adc_vlg,adc_temp;
    float volt,deg;

    lcd_init();
		lcd_cgram();
    i2c_init();
    spi0_init();
	  adc_init();
    uart0_init(9600);

    uart0_tx_string("pot+temp+ldr\r\n");

    /* Set time */
    i2c_send(0xD0,0x00,0x55); // sec
    i2c_send(0xD0,0x01,0x59); // min
    //i2c_send(0xD0,0x02,0x11); // h(24Hrs)
	i2c_send(0xD0,0x02,0x51);

    /* Set date */
    i2c_send(0xD0,0x04,0x31); // dt
    i2c_send(0xD0,0x05,0x12); // mon
    i2c_send(0xD0,0x06,0x25); // yr


    while(1)
    {
			time_data(); //calling time and date func

			
        /*pot*/
        adc_vlg=adc_read(2); //AD0.2
			
        volt=(adc_vlg*3.3)/1023;
				volt=adc_to_voltage(adc_vlg);
        uart0_tx_string(" Volt:");
        //uart0_tx_float(volt);
				uart0_printnum(adc_vlg);
        uart0_tx_string(" V");
				
				/*volt lcd*/
			lcd_string(" ");
				lcd_cmd(0x8A);
				lcd_string("     ");   // clear old voltage (x.xx)
				lcd_cmd(0x8A);
		 	lcd_string(" ");
				lcd_float(volt);
				//lcd_cmd(0x8F);
				lcd_data('V');

			/* temp*/
        adc_temp=adc_read(1);//Ad0.1
				deg=(adc_temp*3.3*100)/1023;
        //deg=adc_to_temp(ch0);
        
				uart0_tx_string(" Temp:");
        //uart0_tx_float(deg);
				uart0_printnum(adc_temp);
        uart0_tx_string(" deg");
				
				/*lcd temp*/
				lcd_cmd(0xC0);
				lcd_string("   ");//clear
				lcd_cmd(0xC0);
				lcd_string("T:");
				lcd_integer(deg);
				lcd_data(1);
				lcd_data('C');
				lcd_string("  ");


/*----------------------------------------*/
        /*LDR sen*/
       ch2=mcp3204_adc_read(2); //ch2
       light=adc_to_light(ch2);
       uart0_tx_string(" Light:");
       uart0_printnum(light);
			  //uart0_printnum(ch2);
       uart0_tx_string("%\r\n");
				
				/*lcd light*/
			//lcd_cmd(0xC0);
			lcd_string("  ");//clear
			//lcd_cmd(0xC0);
			lcd_string("L:");
			lcd_integer(light);
			lcd_data(0);
			
			lcd_data(' ');
       delay_ms(1000);
			//lcd_cmd(0x01);
    }
}
