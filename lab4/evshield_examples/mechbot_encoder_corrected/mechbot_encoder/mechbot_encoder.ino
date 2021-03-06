//program mechbot_encoder

#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)   {
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  
  //set the port direction for encoders, 0 for input
  DDRC &= ~((1<<PC2)|(1<<PC3));
  //set the internal resistors to pull up
  PORTC |= (1<<PC2) | (1<<PC3);

  while (1)  {
    //read the port and test for encoders
    if (PINC & (1<<PC2))   {
      lcdPrint("left=1 ");
    }
    else   {
      lcdPrint("left=0 ");
    }
    
    if (PINC & (1<<PC3))   {
      lcdPrint("right=1");
    }
    else   {
      lcdPrint("right=0");
    }
    
    moveLCDCursor(16);
    lcdPrintByte(PINC);
    delay_ms(10);
    clrLCD();
    moveLCDCursor(0);
  }
}


