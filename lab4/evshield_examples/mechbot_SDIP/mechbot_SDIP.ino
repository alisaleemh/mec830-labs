//program mechbot_SDIP
#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)   {
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  
  //set the port direction for SDIP, 0 for input
  DDRC &= ~((1<<PC5)|(1<<PC4)|(1<<PC3)|(1<<PC2));
  //set the internal resistors to pull up
  PORTC |= (1<<PC2) | (1<<PC3) | (1<<PC4) | (1<<PC5);

  while (1)  {
    //read the port and test for switch S2
    if (PINC & (1<<PC3))   {
      lcdPrint("PC3 is hi");
    }
    else   {
      lcdPrint("PC3 is low");
    }
    moveLCDCursor(16);
    lcdPrintByte(PINC);
    delay_ms(1000);
    clrLCD();
    moveLCDCursor(0);
  }
}


