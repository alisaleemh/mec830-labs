
#include <Wire.h>
#include <EVShield.h>

EVShield          evshield(0x34,0x36);

void  setup()  {
    
    evshield.init( SH_HardwareI2C );

    //light up the left LED (red, green, blue)
    evshield.bank_a.ledSetRGB(64,0,255);
    delay(3000);
    evshield.bank_a.ledSetRGB(0,0,0);

    //light up the right LED
    evshield.bank_b.ledSetRGB(0,128,0);
    delay(3000);
    evshield.bank_b.ledSetRGB(0,0,0);

    //light up both LED's
    evshield.ledSetRGB(64,128, 0);
    delay(3000);
    evshield.ledSetRGB(0,0,0);
    
}

void  loop()  {
}

