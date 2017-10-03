#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)   {
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  
  //set the port direction for switch S4, 0 for input
  DDRC &= ~(1<<PC1);
  

  while (1)  {
    //read the port and test for switch S4
    if (PINC & (1<<PC1))   {
      lcdPrint("PC1 is hi");
    }
    else   {
      lcdPrint("PC1 is low");
    }
    moveLCDCursor(16);
    lcdPrintByte(PINC);
    delay_ms(1000);
    clrLCD();
    moveLCDCursor(0);
  }
}


