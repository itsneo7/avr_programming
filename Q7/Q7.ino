unsigned val = 0b00011000;  
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