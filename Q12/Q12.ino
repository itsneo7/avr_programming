void setup() 
{
  DDRA &= ~(1 << PA7);   
  PORTA |= (1 << PA7);   
  DDRA |= 0b01010101;    
}         

void loop()  
{
  if (~PINA & (1 << PA7)) 
  {
    PORTA = ((~PINA << 1) + 1);
  }
  else
  {
    PORTA = (~PINA << 1);
  }
}
