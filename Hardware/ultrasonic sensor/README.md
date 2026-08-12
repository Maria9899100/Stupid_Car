
## HC-SR04 Ultrasonic Sensor — Pin Configuration (Arduino Nano)

| HC-SR04 Pin | Connect To | Purpose |
|---|---|---|
| VCC | Nano 5V | Power supply (HC-SR04 needs 5V, not 3.3V) |
| Trig | Any digital pin (e.g., D9) | Sends the trigger pulse to start measurement |
| Echo | Any digital pin (e.g., D10) | Receives the reflected pulse — measured to calculate distance |
| GND | Nano GND | Common ground |

**Wiring example:**

Nano 5V → HC-SR04 VCC
Nano D9 → HC-SR04 Trig
Nano D10 → HC-SR04 Echo
Nano GND → HC-SR04 GND


**Notes:**
- Trig and Echo can be **any digital pins** — PWM capability isn't required since you're just sending/reading pulses with `pulseIn()`.
- Some guides recommend a **voltage divider** (e.g., 1kΩ and 2kΩ resistors) on the Echo line for 3.3V-only boards — **not necessary on the Nano**, since it's 5V-tolerant.
- Basic Arduino code pattern:
```cpp
  const int trigPin = 9;
  const int echoPin = 10;

  void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
  }

  void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distanceCm = duration * 0.034 / 2;

    Serial.println(distanceCm);
    delay(500);
  }
```
- Effective range: **2 cm to 400 cm**, with a ~15° detection cone — keep that in mind for sensor placement.

