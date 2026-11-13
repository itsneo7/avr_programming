#include<avr/io.h>
void setup() 
{
   DDRA |=  0xFF;
   PORTA = 0x02;
}

void loop() 
{
  if(PORTA == 0x02)
  {
    _delay_ms(100);
    PORTA |= 0x02;
  }
  if(PORTA>0x80)
  {
     _delay_ms(100);
    PORTA &=~ 0xFF;
    _delay_ms(100);
    PORTA=0x02;
  }
   _delay_ms(100);
   PORTA |= PORTA<<2;
}
