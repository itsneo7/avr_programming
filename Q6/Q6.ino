unsigned val = 0b10000001;  
void setup() 
{
  DDRA = 0xFF; 
}

void loop() 
{ 
  PORTA |= val;
  val = (val << 1) | (val >> 1); 
  delay(500);
}