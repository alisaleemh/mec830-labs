
#include <Wire.h>
#include <EVShield.h>


  //declare EVShield as evshield
  EVShield          evshield(0x34,0x36);


void leftCan() {


    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    1, 90, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );
    _delay_ms(1000);

  evshield.bank_a.motorRunRotations(SH_Motor_1,
    SH_Direction_Reverse,
    10, 2, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );





  _delay_ms(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Forward,
    1, 90, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );



   _delay_ms(1000);

  evshield.bank_a.motorRunRotations(SH_Motor_1,
    SH_Direction_Forward,
    10, 2, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );

  _delay_ms(5000);

}

  void rightCan() {


            evshield.bank_a.motorRunDegrees(SH_Motor_2,
          SH_Direction_Reverse,
          1, 90, SH_Completion_Wait_For,
          SH_Next_Action_Brake
        );

            _delay_ms(1000);


          evshield.bank_a.motorRunRotations(SH_Motor_1,
            SH_Direction_Forward,
            10, 2, SH_Completion_Wait_For,
            SH_Next_Action_Brake
          );





        _delay_ms(1000);

          evshield.bank_a.motorRunDegrees(SH_Motor_2,
          SH_Direction_Forward,
          1, 90, SH_Completion_Wait_For,
          SH_Next_Action_Brake
        );

          _delay_ms(1000);

          evshield.bank_a.motorRunRotations(SH_Motor_1,
            SH_Direction_Reverse,
            10, 2, SH_Completion_Wait_For,
            SH_Next_Action_Brake
          );

          _delay_ms(5000);


  }

void setup()   {



  //set up hardware protocol to the EVshield
  evshield.init( SH_HardwareI2C );

  // reset motors.
  evshield.bank_a.motorReset();


}

void loop(){

  if ( evshield.getButtonState(BTN_LEFT) == true ) {

    leftCan();

  }
  if ( evshield.getButtonState(BTN_RIGHT) == true ) {

    rightCan();
  }

  delay(1000);
  evshield.ledSetRGB(0,0,0);


}
