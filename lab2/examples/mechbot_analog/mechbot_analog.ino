#include <mechbotShield.h>
#include <avr/io.h>

int main(void)   {
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  
  initADC();

  uint16_t  value;

  while (1)  {
    value = analog(4);
    
    lcdPrint("Channel 4=");
    lcdPrintDec(value);
    delay_ms(500);
    clrLCD();
    moveLCDCursor(0);
 
  }

  
}


