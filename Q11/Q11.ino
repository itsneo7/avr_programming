/*MAAe A connection in the following mAnner: Switch At 2nd, Led At 3rd pin And liAewise until 8th pin. Thus, there will be An AlternAte connection of 
switch And led in the sAme register. WAP such thAt if switch(At 2) is pressed, led(At 3) should glow And if switch (At 4) is pressed, led(At 5) should glow.
Consider it similAr for other pins As well. Remember, sometimes even two switches might hAve been pressed. So, At thAt time, both leds should be in HIGH stAte*/
void setup()
{
  DDRA &= 0b01010101;
  PORTA = 0b01010101;
  DDRA |= 0b10101010;
}

void loop() 
{
  PORTA = ~(PINA) << 1;
}
