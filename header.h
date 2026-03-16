#include<LPC21xx.h>
typedef unsigned int u32;
typedef unsigned char u8;
typedef char s8;
typedef int s32;


extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned int cmd);
extern  void lcd_init(void);
extern void lcd_float(double f);
extern void lcd_integer(int num);
extern void lcd_intarr(unsigned int num);
extern void lcd_string(char *);


//uart headers
extern void uart0_tx_string(unsigned char *ptr);
extern void uart0_rx_string(char *p,unsigned int n);
extern unsigned char uart0_rx(void);
extern void uart0_init(unsigned int baud);
extern void uart0_printnum(int n);
extern int uart0_integer(const char *p);
extern void uart0_tx(unsigned int data);
//extern float uart0_rx_float();
extern void uart0_tx_float(float f);
extern void uart0_hexa(unsigned int num);
extern void uart0_tx_float(float f);
extern void uart0_tx_hex(unsigned int num);


/*interrupts headers*/
extern void EINT0_handler(void)__irq;
extern void config_vic_enti0(void);
extern void config_enti0(void);
extern void config_enti1(void);

extern void config_uart0_intr(void);
extern void uart0_Handler(void)__irq;
/*timer*/
extern void timer1_init(void);
extern void vic_timer1_init(void);

extern void press_init(void);
extern void EINT0_Handler(void) __irq;


//spi
extern void spi0_init(void);
/*mcp*/
extern unsigned int mcp3204_adc_read(char ch_num);
//extern char mcp3204_adc_read(char);


//I2C
extern char i2c_receive(char ,char );
extern void i2c_send(char,char  ,char );
extern void i2c_init(void);
/*RTC*/
extern char* day_week(char );

//sensors
extern float adc_to_temp(unsigned int);
extern void adc_init(void);
extern unsigned int adc_read(unsigned int);



//extern float adc_to_light(unsigned int );
extern float adc_to_voltage(unsigned int );
extern unsigned int adc_to_light(unsigned int);












