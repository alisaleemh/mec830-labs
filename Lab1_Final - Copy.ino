#include <mechbotShield.h>
#include <USART.h>
#include <avr/io.h>

int vel = 300, tvel = 500, lsen_hi = 800, lsen_low = 600;

/* 2-d array [ sensor1[on-line, not-on-line, edge], sensor2[on-line, not-on-line, edge]// */
int sensorCalib[4][3] = {
    { 800, 300, 600 },
    { 800, 300, 600 },
    { 800, 300, 600 },
    { 800, 300, 600 }
};

// line sensor array
int lineSensor[4] ;

void moveStraight();
void turnRight();
void turnLeft();
void initialize();
void readLineSensor();

int main(void)
{
    initialize();
    while (1) {
        readLineSensor();


        clrLCD();

        if (lineSensor[1] >= sensorCalib[1][3] && lineSensor[2] >= sensorCalib[2][3] && lineSensor[0] >= sensorCalib[0][3] && lineSensor[3] >= sensorCalib[3][3] ) {
            stopIntersection();
        }
        else if (lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[0] < sensorCalib[0][2] && lineSensor[3] < sensorCalib[3][2] ) {
            moveStraight();
        }

        else if (lineSensor[0] >= sensorCalib[0][2] && lineSensor[1] >= sensorCalib[1][2] && lineSensor[2] < sensorCalib[2][2] && lineSensor[3] < sensorCalib[3][2]) {
            turnLeft();
        }

        else if (lineSensor[3] >= sensorCalib[3][2] && lineSensor[2] >= sensorCalib[2][2] && lineSensor[0] < sensorCalib[0][2] && lineSensor[1] < sensorCalib[1][2]) {
            turnRight();
        }

        else if (lineSensor[3] < sensorCalib[3][1] && lineSensor[2] < sensorCalib[2][1] && lineSensor[0] < sensorCalib[0][1] && lineSensor[1] < sensorCalib[1][1]) {
            stationary();
        }

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

void moveStraight()
{
    motor(vel, vel);
    moveLCDCursor(0);
    lcdPrint("Straight");
    return NULL;
}

void turnRight()
{
    motor(tvel, 0);
    moveLCDCursor(0);
    lcdPrint("Right");
    return NULL;
}
void turnLeft()
{
    motor(0, tvel);
    moveLCDCursor(0);
    lcdPrint("Left");
    return NULL;
}

void stationary()
{
    motor(0,0);
    moveLCDCursor(0);
    lcdPrint("Stationary");
}
