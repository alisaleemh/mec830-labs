
#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTTouch.h>

//touch sensor should be connected to BAS1

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_NXTTouch myTouch; //  Create our sensor for use in this program

void setup()
{

    evshield.init( SH_HardwareI2C );

    //associate myTouch with evshield BAS1
    myTouch.init( &evshield, SH_BAS1 );

}

void  loop()
{
    
    if ( myTouch.isPressed() == true )  {
      evshield.bank_a.ledSetRGB(64,0,255);
    }

    delay(1000);
    evshield.ledSetRGB(0,0,0);
}

