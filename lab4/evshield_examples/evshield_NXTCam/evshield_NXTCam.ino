//EVShield NXTcam
#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTCam.h>
#include <USART.h>


EVShield    evshield(0x34,0x36);
EVs_NXTCam myCam;  //make object myCam

// declare varibales
int         nblobs;
uint8_t         color[8];
uint8_t         left[8];
uint8_t         top[8];
uint8_t         bottom[8];
uint8_t         right[8];




void setup()
{
  
  initUSART();
  printString("starting NXTCam program");
  evshield.init( SH_HardwareI2C );
  myCam.init( &evshield, SH_BAS1 );

  // if there was previous run of this program,
  // the tracking might still be on, so disable it.
  myCam.disableTracking();

  // setup myCam for Object mode and sort by size.
  // also let it begin tracking.
  myCam.selectObjectMode();
  myCam.sortSize();
  myCam.enableTracking();
  delay(1000);
}


void loop()
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
    }
    if(color[i]==3)  {
      printString("blue blob found at: X: ");
      printWord((left[i]+right[i])/2);
      printString(" Y: ");
      printWord((top[i]+bottom[i])/2);
      printString("\r\n");
    }
  }

  

}


