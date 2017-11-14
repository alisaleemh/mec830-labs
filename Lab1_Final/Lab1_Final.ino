#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int vel = 300, tvel = 500, lsen_hi = 800, lsen_low = 600;
int error = 0 ; int previousError = 0 ;
double Kp = 90 ; double Kd = 20 ; double Ki = 0.00001 ;
int motorSpeed = 300 ;
int leftMotorSpeed = 0, rightMotorSpeed = 0;
double P ;
double I ;
double D ;
double PIDvalue;

/* 2-d array [ sensor1[on-line, not-on-line, edge], sensor2[on-line, not-on-line, edge]// */
int sensorCalib[4][3] = {
    { 800, 450, 600 },
    { 800, 450, 600 },
    { 800, 450, 600 },
    { 800, 600, 600 }
};

// line sensor array
int lineSensor[4] ;

void moveStraight();
void turnRight();
void turnLeft();
void initialize();
void readLineSensor();
void calculatePidError();
double calculatePidValue();
void PidMotorControl(double PIDvalue);

int main(void)
{
    initialize();

    while (1) {
        readLineSensor();
        calculatePidError();
        PidMotorControl(calculatePidValue());
    }

}

void calculatePidError () {
    // line sensors = 1 1 1 1
    if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2] ) {
        error = 10 ;
    }
    // line sensors = 1 0 0 1
    else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2] ) {
        error = 10 ;
    }
    // line sensors = 1 1 0 1
    else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2] ) {
        error = 10 ;
    }
    // line sensors = 1 0 1 1
    else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[3] >= sensorCalib[3][2] ) {
        error = 10 ;
    }

    // line sensors = 1 0 0 0
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
    P = error;
    I = I + error;
    D = error-previousError;
    PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
    previousError = error;

    return PIDvalue ;
}

void PidMotorControl(double PIDvalue) {

    if (PIDvalue == 10)
    {

        leftMotorSpeed = 0;
        rightMotorSpeed = 0;
        motor(leftMotorSpeed, rightMotorSpeed);
        beep(3000, 3000000);
        moveLCDCursor(0);
        lcdPrint("Stopped");
    }
    else {
        leftMotorSpeed = motorSpeed + PIDvalue;
        rightMotorSpeed = motorSpeed - PIDvalue;

        constrain(leftMotorSpeed, 0, 1000);
        constrain(rightMotorSpeed, 0 , 1000);

        motor(leftMotorSpeed, rightMotorSpeed);
    }

}




void initialize()
{
    //ADC lineSensor sensors
    DDRD &= ~(1 << PD3);
    PORTD |= 0b00000000;

    //setting bumper button as input
    DDRD &= ~(1 << PD4);
    PORTD |= (1 << PD4);

    //setting motors as output
    DDRB |= ((1 << PB1) | (1 << PB2));
    PORTB &= ~((1 << PB1) | (1 << PB2));

    initSoftSerial();
    initMotor();
    setLCDBackLight(255);
    moveLCDCursor(0);
    initADC();
}

void readLineSensor()
{
    for (int i=0 ; i <= 3 ; i++) {
        lineSensor[i] = analog(i);
    }
}
void stopIntersection()
{
    motor(0, 0);
    beep(3000, 3000000);
    moveLCDCursor(0);
    lcdPrint("Stopped");
    return NULL;
}
