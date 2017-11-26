
#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTCam.h>
#include <USART.h>


//declare EVShield as evshield
EVShield          evshield(0x34,0x36);
EVs_NXTCam        myCam;

// declare varibales
int             nblobs;
uint8_t         color[8];
uint8_t         left[8];
uint8_t         top[8];
uint8_t         bottom[8];
uint8_t         right[8];
uint8_t         direction;

int blue = 1;
int red = 0;
int dropOffBool = 0;

void leftCan() {

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    1, 120, SH_Completion_Dont_Wait,
    SH_Next_Action_Brake
  );
    _delay_ms(1000);

  evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Reverse,
    10, 495, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );





  _delay_ms(1000);

    evshield.bank_a.motorRunUnlimited(SH_Motor_2,
    SH_Direction_Forward,
    1
  );



   _delay_ms(1000);

  evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Forward,
    10, 495, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );

  _delay_ms(1000);
}

 void rightCan() {

      evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    1, 120, SH_Completion_Dont_Wait,
    SH_Next_Action_Brake
  );

      _delay_ms(1000);


    evshield.bank_a.motorRunDegrees(SH_Motor_1,
      SH_Direction_Forward,
      10, 495, SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );





  _delay_ms(1000);

    evshield.bank_a.motorRunUnlimited(SH_Motor_2,
    SH_Direction_Forward,
    1
  );

    _delay_ms(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_1,
      SH_Direction_Reverse,
      10, 495, SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );

    _delay_ms(1000);


 }

 void dropOff() {


     if (blue == 1 && red == 0) {
         dropBlue();
         red = 1;
         blue = 0;
     }
     else if (blue == 0 && red == 1) {
         dropRed();
         red = 0;
         blue = 1;
     }
 }
// red is right
 void dropRed() {
     evshield.bank_a.motorRunDegrees(SH_Motor_1,
       SH_Direction_Forward,
       10, 495, SH_Completion_Wait_For,
       SH_Next_Action_Brake
     );
     _delay_ms(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
        SH_Direction_Reverse,
        1, 30, SH_Completion_Dont_Wait,
        SH_Next_Action_Brake
    );

    _delay_ms(1000);


    evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Reverse,
    10, 495, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );
    _delay_ms(1000);
    evshield.bank_a.motorRunDegrees(SH_Motor_2,
        SH_Direction_Forward,
        1, 30, SH_Completion_Dont_Wait,
        SH_Next_Action_Brake
    );



    _delay_ms(1000);
 }

 void dropBlue() {
     evshield.bank_a.motorRunDegrees(SH_Motor_1,
       SH_Direction_Reverse,
       10, 495, SH_Completion_Wait_For,
       SH_Next_Action_Brake
     );
     _delay_ms(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
        SH_Direction_Reverse,
        1, 30, SH_Completion_Dont_Wait,
        SH_Next_Action_Brake
    );

    _delay_ms(1000);


    evshield.bank_a.motorRunDegrees(SH_Motor_1,
    SH_Direction_Forward,
    10, 495, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );

    _delay_ms(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
        SH_Direction_Forward,
        1, 30, SH_Completion_Dont_Wait,
        SH_Next_Action_Brake
    );



    _delay_ms(1000);
 }


void setup()   {

    initUSART();
    //set up the Rx pin as input (PB0)
    DDRB  &= ~((1 << PB0) | (1 << PB1));
    PORTB &= ~((1 << PB0) | (1 << PB1));

    //set up hardware protocol to the EVshield
    evshield.init( SH_HardwareI2C );

    myCam.init( &evshield, SH_BAS1 );
    // setup myCam for Object mode and sort by size.
    // also let it begin tracking.
    myCam.selectObjectMode();
    myCam.disableTracking();
    myCam.sortSize();
    myCam.enableTracking();

    //initiate hardware USART on EVSheild RXD
    Serial.begin(9600);


    // reset motors.
    evshield.bank_a.motorReset();


}

void loop(){

    if (PINB & (1<<PB1))
    {
        if (dropOffBool == 1) {
            dropOff();
            _delay_ms(1000);
            dropOffBool = 0;
        }
        else if (dropOffBool == 0){
            leftCan();
            _delay_ms(1000);
            dropOffBool = 1;
        }
    }
    else if (PINB & (1<<PB0))
    {
        if (dropOffBool == 0){
            rightCan();
            _delay_ms(1000);
            dropOffBool = 1;
        }
        else if (dropOffBool == 1) {
            dropOff();
            _delay_ms(1000);
            dropOffBool = 0;
        }
    }
}
