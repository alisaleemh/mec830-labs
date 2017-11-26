    #include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>
#include <util/delay.h>

#define CAN_LEFT 0
#define CAN_RIGHT 1

int error = 0 ; int previousError = 0 ;


double Kp = 150 ; double Kd = 5 ; double Ki = 0.00001 ;
int motorSpeed = 300 ;
int leftMotorSpeed = 0, rightMotorSpeed = 0;
double P ;
double I ;
double D ;
double PIDvalue;

int canDirection = 2;
char canDirectionChar[12];
int intersections = 1;
/* 2-d array [ sensor1[on-line, not-on-line, edge], sensor2[on-line, not-on-line, edge]// */
int sensorCalib[4][3] = {
    { 900, 600, 600 },
    { 900, 600, 600 },
    { 900, 600, 600 },
    { 900, 800, 800 }
};

int distanceCalib[2] = {250, 250} ;

char str[16];

// line sensor array
int lineSensor[4] ;
int distanceSensor[2];

void moveStraight();
void turnRight();
void turnLeft();
void initialize();
void readLineSensor();
void calculatePidError();
void checkForCollision();
void PidMotorControl(double PIDvalue);
void initializeCom();
int getCanDirection();
double calculatePidValue();

int main(void)
{
    initialize();
    initializeCom();

    while (1) {
        checkForCollision();
        readLineSensor();
        readDistanceSensor();
        calculatePidError();
        PidMotorControl(calculatePidValue());

    }

}

// function definitions
void initialize()
{

    // OUTPUT DDRB = 1
    // INPUT DDRB = 0
    //ADC lineSensor sensors


    //setting bumper button as input
    DDRC &= ~(1 << PC1);
    PORTC |= (1 << PC1);
    DDRD &= ~((1 << PD3) | (1 << PD4) | (1 << PD5)); //ADC analog sensors
    PORTD |= 0b00000000;



    // //setting motors as output
    // DDRB |= ((1 << PB1) | (1 << PB2));
    // PORTB &= ~((1 << PB1) | (1 << PB2));

    //LED PB0-5 as OUTPUT and Motor
    DDRB |= ((1 << PB1) | (1 << PB2) | (1 << PB3)| (1 << PB4)| (1 << PB5)); //setting motors as output
    PORTB &= ~((1 << PB1) | (1 << PB2)| (1 << PB3)| (1 << PB4)| (1 << PB5));


    initSoftSerial();
    initMotor();
    setLCDBackLight(255);
    moveLCDCursor(0);
    initADC();
}

void initializeCom()
{
    DDRC |= (1 << PC4) |    (1 << PC5);
    PORTC &= ~((1<<PC4) | (1<<PC5));

}
void calculatePidError () {
     // line sensors = 1 1 1 1
     if (lineSensor[0] >= sensorCalib[0][0] && lineSensor[1] >= sensorCalib[1][0] && lineSensor[0] >= sensorCalib[2][0] && lineSensor[3] >= sensorCalib[3][0] ) {
         error = 10 ;
     }
     // line sensors = 1 0 0 1
     else if (lineSensor[0] >= sensorCalib[0][0] && lineSensor[1] < sensorCalib[1][0] && lineSensor[2] < sensorCalib[2][0] && lineSensor[3] >= sensorCalib[3][0] ) {
         error = 10 ;
     }
     // line sensors = 1 1 1 0

     else if (lineSensor[0] >= sensorCalib[0][0] && lineSensor[1] >= sensorCalib[1][0] && lineSensor[2] >= sensorCalib[2][0] && lineSensor[3] < sensorCalib[3][0] ) {
         error = 10 ;
     }
     // line sensors = 1 1 0 1

     else if (lineSensor[0] >= sensorCalib[0][0] && lineSensor[1] >= sensorCalib[1][0] && lineSensor[2] < sensorCalib[2][0] && lineSensor[3] >= sensorCalib[3][0] ) {
         error = 10 ;
     }

     // line sensors = 1 0 1 1

     else if (lineSensor[0] >= sensorCalib[0][0] && lineSensor[1] < sensorCalib[1][0] && lineSensor[2] >= sensorCalib[2][0] && lineSensor[3] >= sensorCalib[3][0] ) {
         error = 10 ;
     }

     // line sensors = 0 1 1 1

     else if (lineSensor[0] < sensorCalib[0][0] && lineSensor[1] >= sensorCalib[1][0] && lineSensor[2] >= sensorCalib[2][0] && lineSensor[3] >= sensorCalib[3][0] ) {
         error = 10 ;
     }

    //line sensors = 1 0 0 0
    else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2]) {
        error = -3;
    }
    // line sensors = 1 1 0 0
    else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2]) {
        error = -2;
    }
    // line sensors = 0 1 0 0
    else if (lineSensor[0] < sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2] ) {
        error = -1;
    }

    // line sensors = 0 1 1 0
    else if (lineSensor[0] < sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2]) {
        error = 0;
    }

    // line sensors = 0 0 0 1
    else if (lineSensor[0] < sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2]) {
        error = 3;
    }
    // line sensors = 0 0 1 1
    else if (lineSensor[0] < sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2]) {
        error = 2;
    }
    // line sensors = 0 1 0 0
    else if (lineSensor[0] < sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2] ) {
        error = -1;
    }
}

double calculatePidValue () {

    if(error == 10) {
        return -100000 ;
    }

    P = error;
    I = I + error;
    D = error-previousError;
    PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
    previousError = error;


    return PIDvalue ;
}

void PidMotorControl(double PIDvalue) {

    if (PIDvalue == -100000) {
        stopIntersection();
        return;
    }

    leftMotorSpeed = motorSpeed + PIDvalue;
    rightMotorSpeed = motorSpeed - PIDvalue;

    constrain(leftMotorSpeed, 0, 1000);
    constrain(rightMotorSpeed, 0 , 1000);

    motor(leftMotorSpeed, rightMotorSpeed);

}


void readLineSensor()
{
    for (int i=0 ; i <= 3 ; i++) {
        lineSensor[i] = analog(i);
    }
    return;
}
void stopIntersection()
{
    intersections++;
    clrLCD();
    motor(0, 0);
    _delay_ms(50);
    // intersection is even to it is at a dropoff intersection
    if (intersections % 2 == 0) {
      canDirection = getCanDirection();
    }
    // intersections is at a pickup location
    else if (intersections % 2 != 0) {
      canDirection = 2;
    }
    sprintf(str, "%d", intersections);


    if (canDirection == 0) { lcdPrint("Can on left");}
    else if (canDirection == 1) { lcdPrint("Can on right");}
    else if (canDirection == 2) { lcdPrint("Can on dropoff");}
    // if (canDirection == 0) { lcdPrint(str);}
    // else if (canDirection == 1) { lcdPrint(str);}
    // else if (canDirection == 2) { lcdPrint(str);}
    sendToEV(canDirection);
    _delay_ms(250);
    idle();
    _delay_ms(10000);
    canDirection = -1;





    moveLCDCursor(0);
    motor(400,400);
    _delay_ms(800);




}

int getCanDirection()
{
    if (distanceSensor[0] >= distanceCalib[0] && distanceSensor[1] < distanceCalib[1]) {
        return 0 ;
    }
    else if (distanceSensor[0] <= distanceCalib[0] && distanceSensor[1] >= distanceCalib[1]) {
        return 1 ;
    }
    else {
        return NULL;
    }

}

void idle()
{
    PORTC &= ~(1 << PC4);
    PORTC &= ~(1 << PC5);
    return NULL;
}


void sendToEV(int canDirection)
{
    if (canDirection == 0) {
        PORTC &= ~(1 << PC4);
        PORTC |= (1 << PC5);
    }
    else if (canDirection == 1) {
        PORTC |= (1 << PC4);
        PORTC &= ~(1 << PC5);
    }
    else if (canDirection == 2) {
        PORTC |= (1 << PC4);
        PORTC &= ~(1 << PC5);
    }
    else {
        return;
    }
}

void readDistanceSensor()
{
    distanceSensor[0] = analog(4);
    distanceSensor[1] = analog(6);
}

void checkForCollision()
{
    if (((PINC & (1 << PC1)) == 0) || ((PIND & (1 << PD3)) == 0) || ((PIND & (1 << PD4)) == 0) || ((PIND & (1 << PD5)) == 0)) {
        motor(0,0);
        beep(500,500000);
        for(int i=0;i<5;i++)
        {
            PORTB |= ((1 << PB3)| (1 << PB4)| (1 << PB5));
            _delay_ms(100);
            PORTB &= ~((1 << PB3)| (1 << PB4)| (1 << PB5));
            _delay_ms(100);
         }
     }
}
