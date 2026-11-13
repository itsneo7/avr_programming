/*22) Write a program to switch ON the led when push button is pressed and let the led stay in ON condition, unless it is pressed again. (Consider Capslock key as an example)*/
unsigned int P = 0; 
void setup() {
  DDRA = 0x02;    
  PORTA = 0x01;  
}
void loop() 
{
  if ((PINA & 0x01) != P) 
  {
    P = PINA & 0x01;
    if (!P) 
    {      
      PORTA ^= 0x02;
    }
  }
}
/*unsigned int P = 0;
void setup() {
  DDRA = 0x02;  
  PORTA = 0x01;  
}

void loop() 
{
  if (!(PINA & 0x01) && P) 
  { 
    PORTA ^= 0x02; 
  }
  P = (PINA & 0x01);
}*/