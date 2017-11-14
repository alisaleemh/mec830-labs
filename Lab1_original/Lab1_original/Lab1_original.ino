#include <mechbotShield.h>
 #include <USART.h>
 #include <avr/io.h>

 int main (void){

     //ADC analog sensors
     DDRD &= ~(1<<PD3);
     PORTD |= 0b00000000;

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

     int vel =750, tvel = 700, lsen_hi = 800, lsen_low = 600;

 while(1){

    clrLCD();

    while (analog(1)>lsen_hi && analog(2)>lsen_hi){
       motor(vel,vel);
       moveLCDCursor(0);
       lcdPrint("Straight");
    }

    clrLCD();


    clrLCD();

    if (analog(3)>lsen_hi && analog(0)>lsen_hi){

       motor(0,0);
       beep(3000,3000000);

       if ((PIND & (1<<PD4)) == 0){

          clrLCD();

          motor(1000,1000);
          moveLCDCursor(0);
          lcdPrint("Straight");

       }
    }
 }
 }

