void setup() {
  DDRK = 0b10010010;    
  PORTK = 0b01101101;  
}
void loop() 
{
  unsigned int sw = ~PINK & 0b01101101;  
  //unsigned int r = sw << 1;
  //unsigned int l = (sw >> 1) | ((sw & 0x01) << 7);
  PORTK = ((sw << 1) ^ ((sw >> 1) | ((sw & 0x01) << 7))) & 0b10010010;
}