#include <mechbotShield.h>
#include <avr/io.h>



int main (void)  {
  uint8_t i = 42;
  
  
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  lcdPrint("Vincent");
  moveLCDCursor(16);
  lcdPrint("was here");
  delay_ms(2000);

  clrLCD();
  moveLCDCursor(0);
  lcdPrint("Byte ");
  lcdPrintByte(i);
  moveLCDCursor(16);
  lcdPrint("Decimal ");
  lcdPrintDec(i);
  
}

