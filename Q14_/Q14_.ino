void setup() 
{
  DDRA  = 0b00010010;
  PORTA = (~DDRA) & 0xFF; 
}

void loop() 
{
  PORTA = (PORTA & ~((1 << PA1) | (1 << PA4))) | (((PINA ^ (PINA >> 2)) & 1) << PA1) | ((((PINA >> 3) ^ (PINA >> 5)) & 1) << PA4);
}
