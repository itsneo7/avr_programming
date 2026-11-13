void setup() 
{
  DDRA &=~ 0xFF;  
  PORTA = 0xFF;
  DDRC |= 0xFF;  
}

void loop() 
{
  PORTC = PINA;  
}