## L298N Motor Driver Module — Pin Configuration (Arduino Nano)

| L298N Pin | Connect To | Purpose |
|---|---|---|
| IN1 | Any digital pin (e.g., D7) | Direction control — Motor A |
| IN2 | Any digital pin (e.g., D8) | Direction control — Motor A |
| IN3 | Any digital pin (e.g., D4) | Direction control — Motor B |
| IN4 | Any digital pin (e.g., D2) | Direction control — Motor B |
| ENA | A **PWM** pin (D3, D5, D6, D9, D10, D11) | Speed control — Motor A |
| ENB | A **PWM** pin (D3, D5, D6, D9, D10, D11) | Speed control — Motor B |
| OUT1, OUT2 | Motor A terminals | Output to Motor A |
| OUT3, OUT4 | Motor B terminals | Output to Motor B |
| 5V | Nano 5V *(only if the L298N's onboard 5V regulator jumper is removed)* | Logic power |
| GND | Nano GND | Common ground — **must** be shared between Nano, driver, and battery |
| 12V / VMS | External battery/supply (6–12V) | Motor power — **not** the Nano's 5V or VIN |

**Wiring example:**

Nano D9 (PWM) → ENA
Nano D7 → IN1
Nano D8 → IN2
Nano D10 (PWM) → ENB
Nano D4 → IN3
Nano D2 → IN4
Nano GND → L298N GND (and battery GND)
Battery + → L298N 12V/VMS


**Notes:**
- **Never power motors from the Nano's 5V or VIN pin.** Motors draw far more current than the Nano can safely supply — always use a separate battery/power supply for the L298N's 12V/VMS input.
- **Common ground is mandatory** — tie Nano GND, L298N GND, and battery GND all together, even though the motor power comes from a separate source.
- The L298N board has an onboard **5V regulator jumper**. If it's in place, the board can supply 5V logic power *from* the battery — you can then skip connecting Nano 5V to it. If your battery is above 12V, remove the jumper and power logic separately to avoid overheating the regulator.
- ENA/ENB control speed via PWM (`analogWrite()`). If you don't need variable speed, tie them directly to 5V for full-speed on/off control.
- Basic Arduino code pattern:
```cpp
  const int enA = 9, in1 = 7, in2 = 8;

  void setup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
  }

  void loop() {
    // Motor A forward at full speed
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255);
  }
```
- The L298N is a **dual H-bridge** — it can drive two DC motors independently, or one stepper motor.
