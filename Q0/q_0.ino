void setup() 
{
  DDRA &= ~0x01; 
  PORTA = 0x01; 
  DDRC =  0x01;    
}

void loop() 
{
  PORTC = ~(PINA);
  
 /* if ((PINA & 0x02) && (PINA & 0x04))
  {
    PORTC = 0x08; 
  }
  else
  {
    PORTC = 0x00; 
  }*/
}
