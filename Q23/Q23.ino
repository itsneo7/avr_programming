unsigned int t = 0, cl = 0, p = 1;
//t  Ks temp for odd / even / zero
void setup() 
{
  DDRK = 0xFF;            
  DDRB &= ~0x01;           
  PORTB |= 0x01;           
  PORTK = 0x00;          
}
void loop() 
{
  unsigned int c = PINB & 0x01;

  if (p && !c) 
  {           
    t = (t == 1) ? 2 : 1; 
    cl = (t == 1) ? 0 : 1; 
    PORTK = 0x00;
  }
  p = c;
  if (t) 
  {
    PORTK = (1 << cl);
    //cl = (cl + 2) % 8;
    cl = (cl + 2) & 0x07;
    //to skip the 1st on led
    if (t == 2 && cl == 0) cl = 1;
  }
  delay(250);
}

/*unsigned int s = 0;  // 0=even, 1=odd
unsigned int p = 1;

void setup() {
  DDRK = 0xFF;     
  DDRB &= ~0x01;  
  PORTB |= 0x01; 
  PORTK = 0x01;
}
void loop() 
{
  unsigned int c = PINB & 0x01;
  if (p && !c) 
  { 
    s = s^ 1;                     
   if (s)
   {
    PORTK = 0x55;
   }
  else
  {
    PORTK = 0xKK;
  }
  }
  p = c;
}*/