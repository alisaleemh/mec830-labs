/*
* Part 2 of 2 for EVShield
* Use this program with mechbot_serial2evshield
*
* This program serial communication from Mechbot pin PC5
* (blue wire on mechbot cable)
* to the hardware RX pin on the  EVShield
*
* NOTE: YOU MUST UNPLUG THE BLUE WIRE FROM THE RXD PIN
*       WHILE UPLOADING YOUR PROGRAM FROM USB
*
*/


#include <Wire.h>
#include <EVShield.h>
#include <avr/io.h>

EVShield          evshield(0x34,0x36);

void  setup()
{
  //set up the Rx pin as input (PD0)
  DDRD &= ~(1<<PD0);
  PORTD |= (1<<PD0);

  //initiate evshield hardware
  evshield.init( SH_HardwareI2C );

  //initiate hardware USART on EVSheild RXD
  Serial.begin(9600);

  //light up both LED's for 3 secs
  evshield.ledSetRGB(64,128, 0);
  delay(3000);
  evshield.ledSetRGB(0,0,0);
  

}

void  loop()
{

  uint8_t c;

  //read in 1 byte form the RXD buffer
  c = Serial.read();

  //test to see if 0x01 was received
  //if ture, light up the left LED
  if (c == 1)
  {
    //light up the left LED (red, green, blue)
    evshield.bank_a.ledSetRGB(0,0,255);
    delay(1000);
    evshield.bank_a.ledSetRGB(0,0,0);

  }

  //if data read from RXD was not 0x01 then light up red LED
  else
  {

    //light up the right LED red
    evshield.bank_b.ledSetRGB(255,0,0);
    delay(1000);
    evshield.bank_b.ledSetRGB(0,0,0);

  }

  delay(500);


}
