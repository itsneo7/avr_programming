#include<avr/io.h>
void setup() 
{
  DDRA |=  0xFF;
  PORTA = 0x01;
}

void loop() 
{
    _delay_ms(100);
  PORTA |= PORTA<<1;
}