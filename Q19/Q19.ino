void setup()
{
    DDRA  = 0b10010010;  // LEDs: PA1, PA4, PA7 outputs
    PORTA = 0b01101101;  // Pull-ups for switches
    DDRC  = 0b01001001;  // LEDs: PC0, PC3, PC6 outputs
    PORTC = 0b10110110;  // Pull-ups for switches
}

void loop()
{
    uint8_t swA = ~PINA, swC = ~PINC;
    PORTA = ~((PORTA & ~0b10010010) |((((swA>>0)&1) ^ ((swA>>2)&1)) << 1) |((((swA>>3)&1) ^ ((swA>>5)&1)) << 4) |((((swA>>6)&1) ^ ((swC>>7)&1)) << 7));
    PORTC = ~((PORTC & ~0b01001001) |((((swA>>0)&1) ^ ((swC>>1)&1)) << 0) |((((swC>>2)&1) ^ ((swC>>4)&1)) << 3) |((((swC>>5)&1) ^ ((swC>>7)&1)) << 6));
}
