#include <mechbotShield.h>
#include <avr/io.h>

int main()
{
  uint8_t i = 42;
  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  Serial.print("Talha");
  moveLCDCursor(16);
  Serial.print("was here");
  delay_ms(2000);

  clrLCD();
  moveLCDCursor(0);
  Serial.print("Byte");
  lcdPrintByte(i);
  moveLCDCursor(16);
  Serial.print("Decimal");
  lcdPrintDec(i);
  
  
}

