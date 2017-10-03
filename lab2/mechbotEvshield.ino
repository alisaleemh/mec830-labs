//mechbotprogram to send signal to EVShield, part 1
//part 2 is to load to EVShieldarduino

#include <mechbotShield.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)   {
  //set the port direction for push button switch S3 and S4 for input
  DDRD &= ~(1<<PD5);
  DDRC &= ~(1<<PC1);
  //set PC4 and PC5 as outputs
  DDRC |= (1<<PC4) | (1<<PC5);
  while(1)
  {
    if (PIND & (1<<PD5))
    {
      PORTC |= (1<<PC4);
    }
    else
    {
      PORTC &= ~(1<<PC4);
    }

    //read the port and test for switch S4
    if (PINC & (1<<PC1))
    {
      PORTC |= ~(1<<PC5);
    }
    else
    {
      PORTC &= ~(1<<PC5);
    }
    delay_ms(1000);
  }
}

