void setup() 
{
  DDRA  = (1 << PA1) | (1 << PA4);
  PORTA = 0x2D; 
  DDRC  = (1 << PC1) | (1 << PC4);
  PORTC = 0x2D;
}
void loop() {
  PORTA = (0x2D) |(((~PINA ^ (~PINA >> 2)) & 1) << PA1) |((((~PINA >> 3) ^ (~PINA >> 5)) & 1) << PA4);
  PORTC = (0x2D) |(((~PINC ^ (~PINC >> 2)) & 1) << PC1) |((((~PINC >> 3) ^ (~PINC >> 5)) & 1) << PC4);
}
