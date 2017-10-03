
#include <Wire.h>
#include <EVShield.h>
#include <USART.h>

EVShield          evshield(0x34,0x36);
int encoderBefore, encoderAfter;



void setup()   {


  //declare EVShield as evshield

  //  set up hardware protocol to the EVshield
  evshield.init( SH_HardwareI2C );

  // reset motors.
  evshield.bank_a.motorReset();
  Serial.begin(9600);

  Serial.print("^Time before \n");
  Serial.print(millis());
  encoderBefore = evshield.bank_a.motorGetEncoderPosition(SH_Motor_1);
  Serial.print("Encoder Position Before\n");
  Serial.print(encoderBefore);



  Serial.print("^Time After Motor\n");
  Serial.print(millis());
  encoderAfter = evshield.bank_a.motorGetEncoderPosition(SH_Motor_1);
  Serial.print("\nEncoder Position Before\n");
  Serial.print(encoderAfter);


}

void loop(){


  while ( evshield.getButtonState(BTN_LEFT) == true ) {

    evshield.bank_a.motorRunUnlimited(SH_Motor_1,SH_Direction_Reverse,SH_Speed_Slow);
      
  }
  
  evshield.bank_a.motorStop (SH_Motor_1, SH_Next_Action_Float);
  
    
  while ( evshield.getButtonState(BTN_RIGHT) == true ) {

    evshield.bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, SH_Speed_Medium, 90, SH_Completion_Wait_For, SH_Next_Action_Brake);
  
  }
  
  evshield.bank_a.motorStop (SH_Motor_1, SH_Next_Action_Float);
  
  
 }
