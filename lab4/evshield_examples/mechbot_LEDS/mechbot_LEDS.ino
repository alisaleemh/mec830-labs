#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>


int main (void)  {
  uint8_t i=0;  //sets up variables i as unsigned int

  //set the data direction registers B and D hi (output)
  DDRB |= (1 << PB0) | (1 << PB1)| (1 << PB3) | (1 << PB4) | (1 << PB5);
  DDRD |= (1 << PD6) | (1 << PD7);

  //start the left most LEDs
  PORTB |= 0b00000011;
  PORTD |= 0b00000000;
  
  
  delay_ms(2000);
  
  for (i=0; i<10; i++)  {
    //toggle the LEDs
    PORTB ^= (1 << PB0) | (1 << PB1);
    PORTD ^= (1 << PD6) | (1 << PD7);
    delay_ms(250);
  }

  //clear the LEDs that were used
  PORTB &= ~((1 << PB0) | (1 << PB1));
  PORTD &= ~((1 << PD6) | (1 << PD7));

  
}

