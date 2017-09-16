#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int main (void){

  //ADC analog sensors
  DDRD &= ~(1<<PD3);
  PORTD |= 0b00000000;

  //setting encoders as input
  DDRC &= ~((1<<PC2)|(1<<PC3));
  PORTC |= (1<<PC2)|(1<<PC3);

  //setting bumper button as input
  DDRD &= ~(1<<PD4);
  PORTD |= (1<<PD4);

  //setting motors as output
  DDRB |= ((1<<PB1)|(1<<PB2));
  PORTB &= ~((1<<PB1)|(1<<PB2));

  initSoftSerial();
  initMotor();
  setLCDBackLight(255);
  moveLCDCursor(0);
  initADC();

  // need to verify lsen_hi and lsen_low in the lab
  // use calibration code from mec 733
  // need to determine Kp,Kd values by trial and error, Kd ougth to be much bigger than Kp
  int vel =700, tvel = 600, lsen_hi = 680, lsen_low = 400, count = 0, low_flag = 0, error, lastError, Kp,Kd;

  while(1){

    clrLCD();

    while (analog(1)>lsen_hi && analog(2)>lsen_hi){
      motor(vel,vel);
      moveLCDCursor(0);
      lcdPrint("Straight");
    }

    clrLCD();

    if (analog(0)>lsen_hi && analog(1)>lsen_hi){

      // PD Controlled Left Turn
      for (count=analog(0);count>lsen_low;count=analog(0)) {

        error = analog(0)-lsen_low;
        tvel =  Kp*error + Kd*(error-lastError);

        motor(-tvel,tvel);
        moveLCDCursor(0);
        lcdPrint("Left");

        lastError=error;
      }
    }

    clrLCD();

    if (analog(2)>lsen_hi && analog(3)>lsen_hi){

      // PD Controlled Right Turn
      for (count=analog(3);count>lsen_low;count=analog(3)) {

        error = analog(3)-lsen_low;
        tvel =  Kp*error + Kd*(error-lastError);

        motor(tvel,-tvel);
        moveLCDCursor(0);
        lcdPrint("Right");

        lastError=error;
      }
    }
    clrLCD();

    if (analog(3)>lsen_hi && analog(0)>lsen_hi){

      disableMotor();
      beep(3000,3000000);

      if ((PIND & (1<<PD4)) == 0){

        for (count=0;count<10;count++){

          clrLCD();
          moveLCDCursor(0);
          motor(vel,vel);
          delay_ms(100);
          moveLCDCursor(0);
          lcdPrint("Straight");

        }

      }
    }
  }
}
