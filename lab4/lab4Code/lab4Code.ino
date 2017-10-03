//mechbotprogram to send signal to EVShield, part 1
//part 2 is to load to EVShieldarduino

#include <mechbotShield.h>
#include <avr/io.h>
#include <USART.h>
#include <util/delay.h>

int main(void)   {

  //set PC4 and PC5 as inputs
  DDRC &= ~((1<<PC4)|(1<<PC5));
  PORTC |= ((1<<PC4)|(1<<PC5));


  //setting motors as output
  DDRB |= ((1<<PB1)|(1<<PB2));
  PORTB &= ~((1<<PB1)|(1<<PB2));

  initSoftSerial();
  initMotor();
  setLCDBackLight(255);
  moveLCDCursor(0);

  int vel = 750;

  while(1){


    //turning left when PC4 is continously pressed
    if (PINC & (1<<PC4))
    {
      clrLCD();

      lcdPrint("right=1");
      motor(vel,-vel);
    }


    
    if (PINC & (1<<PC5))
    {
      clrLCD();
      lcdPrint("left=1");
      motor(-vel, vel);

    }


  }
}


