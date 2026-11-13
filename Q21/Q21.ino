void setup() 
{
  DDRA = 0xAA;  
  PORTA = 0x55;  
  DDRC = 0xAA;   
  PORTC = 0x55;  
}

void loop() {
  uint8_t swA = ~PINA & 0x55;
  uint8_t swC = ~PINC & 0x55;
  uint8_t ra = swA << 1;
  uint8_t la = (swA >> 1) | ((swA & 0x01) << 7);
  PORTA = (ra ^ la) & 0xAA;
  

  uint8_t rc = swC << 1;
  uint8_t lc = (swC >> 1) | ((swC & 0x01) << 7); 
  PORTC = (rc ^ lc) & 0xAA;
}

 //| ((swC & 0x40) >> 5);
 //| ((swA & 0x40) >> 5)