#include <Wire.h>
#include <EVShield.h>

EVShield          evshield(0x34,0x36);

void setup() {

    evshield.init( SH_HardwareI2C );
    
    //wait for go button to continue
    evshield.waitForButtonPress(BTN_GO);
    evshield.ledSetRGB(64,128, 0);
    delay(1000);
    evshield.ledSetRGB(0,0,0);
    
}

void  loop()   {
    
    
    if ( evshield.getButtonState(BTN_LEFT) == true ) {
        evshield.bank_a.ledSetRGB(64,0,255);
    }
    if ( evshield.getButtonState(BTN_RIGHT) == true ) {
        evshield.bank_b.ledSetRGB(0,0,255);
    }

    delay(1000);
    evshield.ledSetRGB(0,0,0);
    
}

