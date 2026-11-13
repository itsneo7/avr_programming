unsigned s=0;
void setup() 
{
   DDRA = 0xFF;
}
void loop() 
{
  if(s < 8)
  {
  PORTA =  (1 << s+1)-1;
  }
  else
  {
    PORTA = 0xFF << (s-6);
  }
  delay(500);
  PORTA = 0;
  delay(200);
  s++;
}
 /*s = ++s % 15;*/