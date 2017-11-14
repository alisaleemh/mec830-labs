//program evshield_nxt_light_ambient.ino
#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_NXTLight.h>

// attach NXT Light Sensor to Port BAS1

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_NXTLight myLight; //  Create our sensor for use in this program

void setup()
{

    evshield.init( SH_HardwareI2C );

    //  initialize the sensor, and tell where it is connected.
    myLight.init( &evshield, SH_BAS1 );
    myLight.setAmbient();

}

void
loop()
{
    
    int16_t light;
    //value of light reading will be 0-1000  0=bright, 1000=dark
    light = myLight.readRaw();

    light = light/4;
  
    evshield.ledSetRGB(0,light,0);
    
    
    delay(250);
}

