#include <Arduino.h>

const int Echo = 10;
const int Trig = 9;

const int In1 = 7;
const int In2 = 8;
const int EnA = 5;

const int In3 = 11;
const int In4 = 12;
const int EnB = 6;

const long threshold = 150;
long duration;
long distance;
void stop()
{
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
}
void forward()
{
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 204); // Ranges from 0 to 255,0 (0% duty cycle,stopped) and 255(100% duty cycle,full speed) 80% duty cycle
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 204);
}
void backward()
{
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(EnA, 51); // Ranges from 0 to 255,0 (0% duty cycle,stopped) and 255(100% duty cycle,full speed) 20% duty cycle
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    analogWrite(EnB, 51);
}
void left()
{
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 51);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 204);
}
void right()
{

    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(EnA, 204);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(EnB, 51);
}

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
void loop()
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    distance = pulseIn(Echo, HIGH, 9000) * 0.034 / 2;
    /* pulseIn() function measures the time taken for the echo to return,
    and we multiply by 0.034 to convert it to centimeters (speed of sound is
    approximately 343 meters per second, or 0.034 cm/µs),and divide by 2
    because the pulse travels to the object and back.
    */

    if (distance > 0 && distance < threshold)
    {
        stop();
        backward();
        delay(500);
        right();
        delay(500);
    }
    else
    {
        forward();
    }
}
