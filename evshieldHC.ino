
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
    1, 120, SH_Completion_Wait_For,
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
    1, 120, SH_Completion_Wait_For,
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
        1, 30, SH_Completion_Wait_For,
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
        1, 30, SH_Completion_Wait_For,
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
        1, 30, SH_Completion_Wait_For,
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
        1, 30, SH_Completion_Wait_For,
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

//   myCam.issueCommand('J'); // lock buffer
//   delay(500);
//
//   myCam.getBlobs(&nblobs, color, left, top, right, bottom);
//   delay(500);
//
//   myCam.issueCommand('K'); // unlock buffer
//
//   printString("number of blobs: ");
//   printWord(nblobs);
//   printString("\r\n");
//
//
//   uint8_t i;
//   for (int i = 0; i < nblobs; i++) {
//     if(color[i]==2)  {
//
//       printString("red blob found at: X: ");
//       printWord((left[i]+right[i])/2);
//       printString(" Y: ");
//       printWord((top[i]+bottom[i])/2);
//       printString("\r\n");
//       direction = ((left[i] + right[i]) /2);
//       printWord(direction);
//     }
//
//     if (direction < 100) {
//       PORTB &= ~(1 << PB0);
//       delay(200);
//       PORTB |= (1 << PB0);
//       delay(2000);
//     }
//
//     if (direction > 100) {
//       PORTB &= ~(1 << PB1);
//       delay(200);
//       PORTB |= (1 << PB1);
//       delay(2000);
//     }
//
//
//
//
//
// }

    // if (((PINB & (1<<PB0)) == 1) & ((PINB & (1<<PB1)) == 0)){
    //     leftCan();
    // }
    // else if (((PINB & (1<<PB0)) == 0) & ((PINB & (1<<PB1)) == 1)){
    //     rightCan();
    // }
    // else if (((PINB & (1<<PB0)) == 1) & ((PINB & (1<<PB1)) == 1)){
    //     evshield.bank_a.ledSetRGB(30,145,255);
    // }
    // changed to if from while and commented out the code
    if (((PINB & (1<<PB0)) == 1) & ((PINB & (1<<PB1)) == 0))
    {
        if (dropOffBool == 0){
            leftCan();
            dropOffBool = 1;
        }
        else if (dropOffBool == 1) {
            dropOff();
            dropOffBool = 0;
        }
    }
    else if (((PINB & (1<<PB0)) == 0) & ((PINB & (1<<PB1)) == 1))
    {
        if (dropOffBool == 0){
            rightCan();
            dropOffBool = 1;
        }
        else if (dropOffBool == 1) {
            dropOff();
            dropOffBool = 0;
        }
    }
}
