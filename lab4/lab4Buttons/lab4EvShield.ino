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
  //set up the Rx pin as output (PB0)
  DDRB |= ((1<<PB0) | (1<<PB1));
  PORTB &= ~((1<<PB0) | (1<<PB1));

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


    while ( evshield.getButtonState(BTN_LEFT) == true ) { 
        PORTB |= (1<<PB1);
        PORTB &= ~(1<<PB0);

    }   
    while ( evshield.getButtonState(BTN_RIGHT) == true ) { 
        PORTB |= (1<<PB0);
        PORTB &= ~(1<<PB1);

    }   



}

