Data aquisaion*/
Main.c
---------
/* uart driver + spi + i2c + mcp + lcd 4bit + delay */
char h,m,s;
char d,mn,y;
#include "header.h"
int main(void)
{
 //char day;
 unsigned int light=0;
 unsigned int ch2=0;
 unsigned int adc_vlg=0,adc_temp=0;
 float volt=0.0,deg=0.0,vout=0.0;
 lcd_init();
 lcd_cgram();
 i2c_init();
 spi0_init();
 adc_init();
 uart0_init(9600);
 uart0_tx_string("Data aquisation system\r\n");
 lcd_string("Data aquisation");
 /* Set time */
 i2c_send(0xD0,0x00,0x55); // sec
 i2c_send(0xD0,0x01,0x59); // min
 //i2c_send(0xD0,0x02,0x11); // h(24Hrs)
 i2c_send(0xD0,0x02,0x51);//12Hrs
 /* Set date */
 i2c_send(0xD0,0x04,0x31); // date
 i2c_send(0xD0,0x05,0x12); // month
 i2c_send(0xD0,0x06,0x25); // year
 while(1)
 {
 time_data(); //calling time and date func
 /*pot*/
 adc_vlg=adc_read(2); //AD0.2 ->29
 volt=(adc_vlg*3.30)/1023;
 uart0_tx_string(" Volt:");
 uart0_tx_float(volt);
 //uart0_printnum(adc_vlg);
 uart0_tx_string(" V");
 /*volt lcd*/
 lcd_string(" ");
 lcd_cmd(0x8A);
 lcd_string(" ");
 lcd_cmd(0x8A);
 lcd_string(" ");
 lcd_data('V');//
 lcd_float(volt);
 lcd_data('v');
 /* temp*/
 adc_temp=adc_read(1);//Ad0.1->28
 vout=(adc_temp*3.3)/1023;
 deg=(vout-0.5)/0.01;
 uart0_tx_string(" Temp:");
 //uart0_printnum(adc_temp);
 uart0_printnum(deg);
 uart0_tx_string(" deg");
 /*lcd temp*/
 lcd_cmd(0xC8);
 lcd_string(" ");//clear
 lcd_cmd(0xC8);
 //lcd_data('T'); //
 lcd_data(2);
 lcd_integer(deg);
 //lcd_data(1); //T:
 //lcd_data('C');
 lcd_data(5);
 lcd_string(" ");
 /*----------------------------------------*/
 /*LDR sen*/
 ch2=mcp3204_adc_read(2); //ch2
 light=(ch2*100)/4095;
 uart0_tx_string(" Light:");
 uart0_printnum(light);
 //uart0_printnum(ch2);
 uart0_tx_string("%\r\n");
 /*lcd light*/
 lcd_cmd(0xCC);
 lcd_string(" ");//clear
 lcd_cmd(0xCC);
 //lcd_string("L:");
 lcd_data(3); //L:
 lcd_integer(light);
 lcd_data('%');
 lcd_data(' ');
 delay_ms(1000);
 //lcd_cmd(0x01);
 }
}