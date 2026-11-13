void setup() 
{
  DDRA &= ~0x01;
  PORTA = 0x01;
  DDRA = 0x02;    
}
void loop() 
{
  PORTA = ~PINA<<1;
}