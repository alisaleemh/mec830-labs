
#include <Wire.h>
#include <EVShield.h>




void setup()   {

    
    //declare EVShield as evshield
    EVShield          evshield(0x34,0x36);  
  
    //set up hardware protocol to the EVshield
    evshield.init( SH_HardwareI2C );

    // reset motors.
    evshield.bank_a.motorReset();
   
//    evshield.bank_a.motorRunUnlimited(SH_Motor_1, 
//                     SH_Direction_Forward, 
//                     SH_Speed_Slow);
//    delay(1000);
    evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Float);

    delay(4000);

    evshield.bank_a.motorRunDegrees(SH_Motor_1, 
                     SH_Direction_Forward, 
                     20, 90, SH_Completion_Wait_For,
                     SH_Next_Action_Brake);

    delay(1000);

//    evshield.bank_a.motorRunRotations(SH_Motor_1, 
//                     SH_Direction_Reverse, 
//                     SH_Speed_Medium,
//                     1, 
//                     SH_Completion_Wait_For,
//                     SH_Next_Action_BrakeHold);

    evshield.bank_a.motorRunRotations(SH_Motor_2, 
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     8, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);


}

void loop(){
  
}



