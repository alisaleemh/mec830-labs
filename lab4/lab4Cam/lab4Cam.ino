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
#include <EVs_NXTCam.h>
#include <avr/io.h>
#include <USART.h>


EVShield          evshield(0x34,0x36);
EVs_NXTCam myCam; 

// declare varibales
int         nblobs;
uint8_t         color[8];
uint8_t         left[8];
uint8_t         top[8];
uint8_t         bottom[8];
uint8_t         right[8];
uint8_t    direction;



void  setup()
{
  initUSART();

  //set up the Rx pin as output (PB0)
  
  DDRB |= ((1<<PB0) | (1<<PB1));
  PORTB &= ~((1<<PB0) | (1<<PB1));

  //initiate evshield hardware
  evshield.init( SH_HardwareI2C );
  myCam.init( &evshield, SH_BAS1 );

  // setup myCam for Object mode and sort by size.
  // also let it begin tracking.
  myCam.selectObjectMode();
  myCam.disableTracking();
  myCam.sortSize();
  myCam.enableTracking();





  //initiate hardware USART on EVSheild RXD
  Serial.begin(9600);

  //light up both LED's for 3 secs
  evshield.ledSetRGB(64,128, 0);
  delay(3000);
  evshield.ledSetRGB(0,0,0);
  

}

void  loop()
{
  myCam.issueCommand('J'); // lock buffer
  delay(500);

  myCam.getBlobs(&nblobs, color, left, top, right, bottom);
  delay(500);

  myCam.issueCommand('K'); // unlock buffer

  printString("number of blobs: ");
  printWord(nblobs);
  printString("\r\n");
    

  uint8_t i;
  for (int i = 0; i < nblobs; i++) {
    if(color[i]==2)  {

      printString("red blob found at: X: ");
      printWord((left[i]+right[i])/2);
      printString(" Y: ");
      printWord((top[i]+bottom[i])/2);
      printString("\r\n");
      direction = ((left[i] + right[i]) /2);
      printWord(direction);
    }

    if (direction < 100) {
      PORTB &= ~(1 << PB0);
      delay(200);
      PORTB |= (1 << PB0);
      delay(2000);
    }

    if (direction > 100) {
      PORTB &= ~(1 << PB1);
      delay(200);
      PORTB |= (1 << PB1);
      delay(2000);
    }

    
  }

   while ( evshield.getButtonState(BTN_LEFT) == true ) { 
        PORTB |= (1<<PB1);
        PORTB &= ~(1<<PB0);

    }   
    while ( evshield.getButtonState(BTN_RIGHT) == true ) { 
        PORTB |= (1<<PB0);
        PORTB &= ~(1<<PB1);

    }   

}


    

  

  







