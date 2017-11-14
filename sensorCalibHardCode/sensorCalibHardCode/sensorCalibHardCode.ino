#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int main (void){
  
  DDRD &= ~(1<<PD3);
  PORTD |= 0b00000000;

  initSoftSerial();
  setLCDBackLight(255);
  clrLCD();
  moveLCDCursor(0);
  initADC();
  uint16_t value;
  int n = 1;

  while(1){

 
      clrLCD();
      value = analog(n);
      lcdPrint("channel");
      lcdPrintDec(n);
      lcdPrint(" = ");
      moveLCDCursor(16);
      lcdPrintDec(value);
      delay_ms(1000);
 
  }
}
