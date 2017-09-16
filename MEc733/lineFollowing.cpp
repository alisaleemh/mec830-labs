#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int setup (void){
  
  DDRD &= ~(1<<PD3);    //ADC analog sensors
  PORTD |= 0b00000000;


  DDRC &= ~((1<<PC2)|(1<<PC3)); //setting encoders as input
  PORTC |= (1<<PC2)|(1<<PC3);

  DDRB |= ((1<<PB1)|(1<<PB2));   //setting motors as output
  PORTB &= ~((1<<PB1)|(1<<PB2));

  initSoftSerial();
  initMotor();
  setLCDBackLight(255);
  moveLCDCursor(0);
  initADC();
}

int run (void) {
  int vel =800;
  int tvel = 600;
  int lsen = 680;
  int count = 0;
  int low_flag=0;

  while (analog(1)>lsen && analog(2)>lsen){
    motor(vel,vel);
    moveLCDCursor(0);
    lcdPrint("Straight");
  }

  clrLCD();

  while (analog(0)>lsen && analog(1)>lsen){
    motor(-vel,vel);
    moveLCDCursor(0);
    lcdPrint("Left");
  }
  clrLCD();

  while (analog(2)>lsen && analog(3)>lsen){
    motor(vel,-vel);
    moveLCDCursor(0);
    lcdPrint("Right");
  }
  clrLCD();

  while (analog(0)>800 && analog(1)>700 && analog(2)>470 && analog(3)>540){
    motor(0,vel);
    moveLCDCursor(0);
    lcdPrint("Sharp left");
  }
}

int main (void){

  setup()

  while(1){
    clrLCD();
    run();
  }
}
