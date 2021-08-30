#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h> 

void command(unsigned char cmd);
void data(unsigned char dt);

int main(void)
{
	DDRB =0xFF;
	DDRC =0xFF;
	
	command(0x01); //clear screen
	command(0x38); // 8bit mode,5*7 pixels
	command(0x0C); // display ON cursor OFF
	_delay_ms(50);
	data(0x59); //ASCII value='Y'
	data(0x4F); //ASCII value='O'
	data(0x21); //ASCII value='!'
	
}

void command(unsigned char cmd)
{
	PORTC |=(0 << PINB0); // RS set to 0
	PORTC |=(0 << PINB1); // RW set to 0
	PORTC |=(1 << PINB2); // E set to 1
	PORTB =cmd;
	_delay_ms(50);
	PORTC &=~(1 << PINB2); // E set to 0 
}
void data(unsigned char at)
{
	PORTC |=(1 << PINB0); // RS set to 1
	PORTC |=(0 << PINB1); // RW set to 0
	PORTC |=(1 << PINB2); // E set to 1
	PORTB =at;
	_delay_ms(50);
	PORTC &=~(1 << PINB2); // E set to 0
}