#include <Arduino.h>

const int Echo = 10;
const int Trig = 9;

const int In1 = 7;
const int In2 = 8;
const int EnA = 5;

const int In3 = 11;
const int In4 = 12;
const int EnB = 6;

const long threshold = 15;
long duration;
long distance;

void setup()
{

    Serial.begin(9600);
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);

    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(EnA, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(EnB, OUTPUT);
}
void stopCar()
{
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
}
void forwardCar()
{
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 153); // Ranges from 0 to 255,0 (0% duty cycle,stopped) and 255(100% duty cycle,full speed) 60% duty cycle
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 153);
}
void backwardCar()
{
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(EnA, 10); // Ranges from 0 to 255,0 (0% duty cycle,stopped) and 255(100% duty cycle,full speed) 3.9% duty cycle
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(EnB, 10);
}
void leftTurn()
{
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 10);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 153);
}
void rightTurn()
{

    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 153);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 10);
}

void loop()
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    duration = (pulseIn(Echo, HIGH, 9000));
    if (distance == 0)
    {
        stopCar();
        return;
    }
    distance = (duration * 0.034) / 2;
    /* pulseIn() function measures the time taken for the echo to return,
    and we multiply by 0.034 to convert it to centimeters (speed of sound is
    approximately 343 meters per second, or 0.034 cm/µs),and divide by 2
    because the pulse travels to the object and back.
    */

    if (distance < threshold)
    {
        stopCar();
        backwardCar();
        delay(500);
        rightTurn();
        delay(500);
    }
    else
    {
        forwardCar();
    }
}
