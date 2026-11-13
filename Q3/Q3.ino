#include<avr/io.h>
void setup() 
{
   DDRA |=  0xFF;
   PORTA = 0x01;
}

void loop() 
{
  if(PORTA == 0x01)
  {
      _delay_ms(1);
    PORTA |= 0x01;
  }
  if(PORTA>0x40)
  {
     _delay_ms(1);
    PORTA &=~ 0xFF;
      _delay_ms(1);
    PORTA=0x01;
  }
   _delay_ms(1);
   PORTA |= PORTA<<2;
}
