#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int vel =750, tvel = 700, lsen_hi = 800, lsen_low = 600;

void moveStraight() ;
void turnRight();
void turnLeft();

  

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



        
while(1){
   
   clrLCD();
    
   while (analog(1)>lsen_hi && analog(2)>lsen_hi){
    moveStraight();
   }
    
   clrLCD();
    
   if (analog(0)>lsen_hi && analog(1)>lsen_hi){
    turnLeft();
   
   }
    
   clrLCD();
  
   if (analog(2)>lsen_hi && analog(3)>lsen_hi){
    turnRight();  
   }   
   
   clrLCD();
       
   if (analog(3)>lsen_hi && analog(0)>lsen_hi){
    stopIntersection();
   }
}
}

void stopIntersection() {
  motor(0,0);
  beep(3000,3000000);
  moveLCDCursor(0);
  lcdPrint("Stopped");
}

void moveStraight () {
    motor(vel,vel);
    moveLCDCursor(0);
    lcdPrint("Straight");
    return NULL;
}

void turnRight () {
      motor(tvel,0);
      moveLCDCursor(0);
      lcdPrint("Right");
      return NULL;
}
void turnLeft () {
      motor(0,tvel);
      moveLCDCursor(0);
      lcdPrint("Left");
      return NULL;
}


