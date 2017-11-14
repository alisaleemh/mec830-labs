
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
    delay(1000);

  evshield.bank_a.motorRunRotations(SH_Motor_1,
    SH_Direction_Forward,
    10, 1, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );





  delay(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Forward,
    1, 90, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );



  delay (1000);

  evshield.bank_a.motorRunRotations(SH_Motor_1,
    SH_Direction_Reverse,
    SH_Speed_Slow, 1, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );
}

  void rightCan() {

      evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Reverse,
    1, 90, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );

      delay(1000);


    evshield.bank_a.motorRunRotations(SH_Motor_1,
      SH_Direction_Reverse,
      10, 1, SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );





  delay(1000);

    evshield.bank_a.motorRunDegrees(SH_Motor_2,
    SH_Direction_Forward,
    1, 90, SH_Completion_Wait_For,
    SH_Next_Action_Brake
  );

    delay (1000);

    evshield.bank_a.motorRunRotations(SH_Motor_1,
      SH_Direction_Forward,
      10, 1, SH_Completion_Wait_For,
      SH_Next_Action_Brake
    );

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


