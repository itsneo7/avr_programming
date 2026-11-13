void setup() {
  DDRK = 0xAA;    
  PORTK = 0x55;  
}

void loop() 
{
  unsigned int sw = ~PINK & 0x55;  
  unsigned int r = sw << 1;
  unsigned int l = (sw >> 1) | ((sw & 0x01) << 7);
  PORTK = (r ^ l) & 0xAA;
}