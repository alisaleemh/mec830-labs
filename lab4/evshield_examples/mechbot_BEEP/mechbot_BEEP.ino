//manually beep the buzzer on PB3, and use beep command
#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>


int main (void)  {
  //set the data direction registers B and D hi (output)
  DDRB |= (1 << PB0) | (1 << PB1)| (1 << PB3) | (1 << PB4) | (1 << PB5);
  DDRD |= (1 << PD6) | (1 << PD7);

  initSoftSerial();
  setLCDBackLight(147);
  clrLCD();
  moveLCDCursor(0);
  lcdPrint("Manual");
  moveLCDCursor(16);
  lcdPrint("Buzzer");
  delay_ms(2000);


  //turn off LEDs
  PORTB |= 0b00000000;
  PORTD |= 0b00000000;

  
  uint16_t i;

  for (i=0; i<500; i++)  {
    PORTB |= (1<<PB3);
    delay_ms(1);
    PORTB &= ~(1<<PB3);
    delay_ms(1);
  }
  
  beep(500, 1000000);
  delay_ms(1000);
  beep(2000, 1000000);

  
}

