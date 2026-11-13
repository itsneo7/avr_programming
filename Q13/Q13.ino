void setup() 
{
  DDRA  = 0b01010101;  
  PORTA = 0b10101010; 
  DDRC  = 0b10101010;  
  PORTC = 0b01010101; 
}
void loop() 
{
  //PORTA = (PORTA & 0b10101010) | (((~PINA & 0b10101010) << 1) | ((~PINC & (1 << PC0)) >> PC0));
  //PORTC = (PORTC & 0b01010101) | ((~PINC & 0b01010101) >> 1);
 PORTA = (PORTA & 0xAA) | ((~PINA & 0xAA) << 1) | ((~PINC & (1 << PC0)) >> PC0);
 PORTC = (PORTC & 0x55) | ((~PINC & 0x55) >> 1) | (~PINA & (1 << PA7));
}


