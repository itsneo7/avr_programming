//Write a program, which enables even numbered output pins to HIGH state, one by one, from 1st to 8th with a delay of 100 ms.
/*Make a connection of 8 switches on one register and 8 leds in other register.1st switch will create a pattern same as program 3,
with delay of 100ms, 2nd with delay of 200ms, 3rd with 300ms and so on. But you are supposed to use only a delay of 100ms.*/

#include <avr/io.h>

unsigned PT = 0x01;

void setup()
{
  DDRA &= ~0xFF;    
  PORTA |= 0xFF;    
  DDRC |= 0xFF;
}
void loop() 
{
  if (PT == 0x80)
  {
    PORTC = PT;
    delay(100 * (~PINA & 0xFF));
    PT = 0x01;
  }
  
  if (~PINA & 0xFF) 
  {
    PORTC = PT;
    PT <<= 1;
    delay(100 * (~PINA & 0xFF)); 
  } 
}



/*#include<avr/io.h>
unsigned PT = 0x01;
unsigned  s;
void setup()
{
  DDRA &=~ 0xFF;
  DDRC |= 0xFF;
}
void loop() 
{
  if(PT == 0x80)
  {
    PORTC = PT;
    delay(100 * PINA);
    PT = 0x01;
  }
 if(PINA)
 {
  PORTC = PT;
  PT = PT << 1;
  delay(100 * PINA);
 } 
}*/








/*if(PT == 0x40)
  {
    PORTC = PT;
    delay(100*s);
    PT = 0x01;
  }
  if(PINA)
  {
  PORTC = PT;
  PT = PT << 2;
  delay(100 * s);
  }
  else
  {
    s = (PINA |= PT);
  }*/