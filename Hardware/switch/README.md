# Arduino Nano V3 (ATmega328P) Obstacle Avoiding Car — Wiring

This document describes the complete electrical wiring of the Arduino Nano
V3 (ATmega328P) obstacle-avoiding car.

The car uses:

- Arduino Nano V3 (ATmega328P)
- HC-SR04 ultrasonic distance sensor
- L298N dual H-bridge motor driver
- 2 × DC geared motors
- 2 × 18650 cells connected in series (2S battery pack)
- ON/OFF switch
- Jumper wires
- Two plastic car wheels
- One Caster wheel
- Car chassis

The Arduino Nano reads the distance measured by the HC-SR04 and controls the
two DC motors through the L298N motor driver. The Arduino itself is powered
directly from the same 2S battery pack, through its VIN pin.

---

# 1. System Overview

The complete system can be thought of as four main sections:

```text
                    HC-SR04
                Ultrasonic Sensor
                       │
                       │ Distance data
                       ▼
                ┌──────────────┐
                │ Arduino Nano │
                └──────┬───────┘
                       │
                       │ Motor control signals
                       ▼
                ┌──────────────┐
                │    L298N     │
                │ Motor Driver │
                └──────┬───────┘
                       │
                 ┌─────┴─────┐
                 ▼           ▼
            Left Motor   Right Motor




             2S 18650 Battery Pack
                       │
                    Switch
                       │
                 ┌─────┴─────┐
                 ▼           ▼
              L298N      Arduino VIN
```
The Arduino is responsible for the logic and decision-making.

The L298N is responsible for supplying current to the motors.

The HC-SR04 provides obstacle-distance information.

The battery pack powers both the L298N (motor supply) and the Arduino Nano
(via VIN) directly.

# 2. Component List

  | Component                    |    Quantity | Purpose                        |
  | ----------------------------- | ----------: | ------------------------------ |
  | Arduino Nano V3 (ATmega328P) |           1 | Main controller                |
  | HC-SR04             |           1 | Obstacle/distance detection    |
  | L298N                |           1 | Dual DC motor driver           |
  | DC geared motor     |           2 | car movement                   |
  | 18650 cell          |           2 | Battery                        |
  | 2S battery pack/BMS |           1 | Battery arrangement/protection |
  | ON/OFF switch       |           1 | Main power control             |
  | Jumper wires        | As required | Electrical connections         |
  | Car wheel           |           2 | Mechanical structure           |
  | Castor wheel        |           1 | Mechanical structure           |
  | Car chassis         |           1 | Mechanical structure           |

## 2.1 Arduino Nano V3 (ATmega328P) — Board Specifics

The wiring in this document assumes the classic Nano V3 board built around
the ATmega328P microcontroller. Relevant specs for this build:

  | Spec                     | Value                                   |
  | ------------------------- | --------------------------------------- |
  | Operating logic voltage   | 5 V                                      |
  | Recommended input voltage (VIN) | 7–12 V                            |
  | Absolute max input voltage (VIN) | 6–20 V (avoid the extremes)       |
  | Digital I/O pins          | D0–D13                                  |
  | PWM-capable pins          | D3, D5, D6, D9, D10, D11                |
  | Onboard voltage regulator | Linear (typically AMS1117 or equivalent)|
  | Flash memory              | 32 KB (0.5 KB used by bootloader)       |
  | Clock speed                | 16 MHz                                  |

This confirms two things used elsewhere in this document:

- The 2S battery pack (~7.4 V nominal, ~8.4 V full charge) sits comfortably
  within the recommended VIN range for this board.
- D5 and D6, used for ENA/ENB PWM speed control, are genuine PWM pins on the
  ATmega328P Nano.

> [!NOTE]
> Some Nano V3 clones use a CH340 USB-to-serial chip and may require
> selecting "ATmega328P (Old Bootloader)" in the Arduino IDE's board menu to
> upload sketches successfully. This does not affect any of the wiring in
> this document — it is a software/upload setting only.

# 3. HC-SR04 Ultrasonic Sensor

The HC-SR04 measures the distance between the car and an obstacle.

It has four pins:
  | HC-SR04 Pin | Arduino Nano | Function       |
  | ----------- | ------------ | -------------- |
  | VCC         | 5V           | Sensor power   |
  | GND         | GND          | Ground         |
  | TRIG        | D9           | Trigger signal |
  | ECHO        | D10          | Echo signal    |

Wiring:

   ```text
   HC-SR04                  Arduino Nano
    
   VCC  ─────────────────── 5V
   GND  ─────────────────── GND
   TRIG ─────────────────── D9
   ECHO ─────────────────── D10
   ``` 
How the sensor works

The Arduino sends a trigger signal from D9.

```text
  Arduino D9
      │
      │ Trigger
      ▼
  HC-SR04
      │
      │ Ultrasonic pulse
      ▼
  Obstacle
      │
      │ Reflection
      ▼
  HC-SR04
      │
      │ Echo signal
      ▼
  Arduino D10
```

The Arduino measures the duration of the echo signal and calculates the
approximate distance to the obstacle.

# 4. Arduino Nano → L298N

The Arduino controls the L298N using six digital pins.

Complete L298N control-pin assignment
  | L298N Pin | Arduino Nano Pin | Function                |
  | --------- | ---------------- | ----------------------- |
  | ENA       | D5               | Left motor speed (PWM)  |
  | IN1       | D7               | Left motor direction 1  |
  | IN2       | D8               | Left motor direction 2  |
  | IN3       | D11              | Right motor direction 1 |
  | IN4       | D12              | Right motor direction 2 |
  | ENB       | D6               | Right motor speed (PWM) |


Therefore:
```text
  
  Arduino Nano              L298N
  
  
  D5  ───────────────────── ENA
  D7  ───────────────────── IN1
  D8  ───────────────────── IN2
  
  
  D11 ───────────────────── IN3
  D12 ───────────────────── IN4
  D6  ───────────────────── ENB
```
Quick pin map
```text
  D5  → ENA
  D6  → ENB
  
  
  D7  → IN1
  D8  → IN2
  
  
  D11 → IN3
  D12 → IN4
  
  
  D9  → HC-SR04 TRIG
  D10 → HC-SR04 ECHO
```
# 5. ENA and ENB — Motor Speed Control

The L298N has two enable pins:
```text
  ENA → Left motor channel
  ENB → Right motor channel
```

ENA and ENB can be controlled using PWM.

The Arduino Nano uses:
```text
  D5 → ENA
  D6 → ENB
```
Both D5 and D6 support PWM.

This allows the software to control motor speed.

Conceptually:
```text
  Higher PWM → Higher motor speed
  Lower PWM  → Lower motor speed
  0 PWM      → Motor stopped
```
ENA/ENB jumpers

Many L298N modules have small jumpers installed on ENA and ENB.

If the Arduino is going to control motor speed using PWM:

Remove the ENA and ENB jumpers.

The Arduino should then control ENA and ENB directly.

If the jumpers remain installed, the module may keep the enable inputs permanently enabled,
depending on the particular L298N module.

# 6. IN1, IN2, IN3 and IN4 — Motor Direction

The four input pins control motor direction.

Left motor
  `IN1 + IN2 → Left motor direction`
Right motor
  `IN3 + IN4 → Right motor direction`
Left motor control
  |  IN1 |  IN2 | Result      |
  | ---: | ---: | ----------- |
  |  LOW |  LOW | Stop        |
  | HIGH |  LOW | Direction 1 |
  |  LOW | HIGH | Direction 2 |
  | HIGH | HIGH | Brake/stop* |

Right motor control
|  IN3 |  IN4 | Result      |
| ---: | ---: | ----------- |
|  LOW |  LOW | Stop        |
| HIGH |  LOW | Direction 1 |
|  LOW | HIGH | Direction 2 |
| HIGH | HIGH | Brake/stop* |


# 7. Motors → L298N

For this project, define:

```text
Motor 1 = Left motor
Motor 2 = Right motor
```

Connect them as follows:
```text
L298N                    Motor

OUT1 ─────────────────── Left motor wire 1
OUT2 ─────────────────── Left motor wire 2

OUT3 ─────────────────── Right motor wire 1
OUT4 ─────────────────── Right motor wire 2
```
Motor direction

The actual direction depends on the physical orientation of the motor and
which wire is connected to which output.

If a motor rotates in the opposite direction from what the software expects,
swap the two wires of that motor:

`OUT1 ↔ OUT2`

or

`OUT3 ↔ OUT4`

depending on which motor needs to be reversed.

Do not change the Arduino pin assignment simply because a motor rotates in
the opposite direction.

# 8. Battery Pack

The car uses two 18650 cells connected in series.

This is commonly called a:

`2S 18650 battery pack`

A typical 18650 Li-ion cell has a nominal voltage of approximately 3.7 V.

Therefore:

`3.7 V + 3.7 V ≈ 7.4 V nominal`

The voltage of a fully charged Li-ion cell is higher than its nominal voltage,
so a typical 2S pack can reach approximately:

`4.2 V + 4.2 V = 8.4 V`

This same pack supplies both the L298N motor driver and, through the
Arduino's VIN pin, the Arduino Nano itself.

# 9. Battery → L298N

The battery positive connection should pass through the ON/OFF switch.
```text
Battery (+)
     │
     ▼
 ON/OFF Switch
     │
     ▼
 L298N +12V
```
The battery negative connection goes to L298N GND:
```text
Battery (-)
     │
     ▼
 L298N GND
```
Important note about the L298N "+12V" label

The `+12V` terminal on many L298N modules is the motor-power input.

It does not mean that the supply must be exactly 12 V.

A 2S battery pack provides approximately 7.4 V nominal, which is within the
motor-driver's usable supply range for many L298N modules.

Always check the specifications of the exact L298N module being used.

# 10. Power Switch

The ON/OFF switch should be placed in series with the battery positive line,
ahead of both the L298N and the Arduino, so a single switch controls power to
the whole car.
```text
Battery (+)
     │
     ▼
   SWITCH
     │
     ▼
  BATTERY+
     │
     ├────────── L298N motor supply
     │
     └────────── Arduino VIN
```
The switch therefore controls the main power supplied to the car, including
the Arduino.

The battery negative should remain connected to the common ground.

# 11. Powering the Arduino Nano

The Arduino Nano is powered directly from the 2S 18650 battery pack, through
its VIN pin. The battery's switched positive output is shared between the
L298N motor supply and the Arduino VIN, and the battery negative is shared
between the L298N GND and the Arduino GND.

```text
Battery (+)
     │
   Switch
     │
     ├──────────── L298N motor supply
     │
     └──────────── Arduino VIN
```
Battery negative:
```text
Battery (-)
     │
     ├──────────── L298N GND
     │
     └──────────── Arduino GND
```

Why VIN, and not 5V

The Arduino Nano's VIN pin feeds the onboard voltage regulator, which steps
the input down to a clean 5 V for the board and its logic. A 2S pack at
roughly 7.4 V nominal (up to ~8.4 V fully charged) falls within the Nano's
typical recommended VIN range, so it can be connected there directly.

Do **not** connect the raw battery voltage to the Arduino's 5V pin — the 5V
pin is a regulated output/input meant for an already-regulated 5 V supply,
and feeding it 7.4–8.4 V directly can damage the board. VIN is the correct
connection point for an unregulated battery supply.

# 12. L298N 5V Pin

The exact function of the 5V pin on an L298N module depends on the module's
onboard regulator and jumper configuration.

Because the Arduino is powered independently from the battery pack via VIN,
it is **not necessary** to connect the L298N's 5V pin to the Arduino at all.

If you do choose to use the L298N's onboard regulator to power the Arduino's
5V pin instead of using VIN, then:

  1. Check the markings on your exact L298N module.
  2. Check whether the 5V regulator jumper is installed.
  3. Check the module's documentation.
  4. Determine whether the 5V pin is an output or an input under that
  configuration.
  5. Only connect it to the Arduino 5V pin (never VIN) if confirmed to be a
  regulated 5 V output.

For this build, the L298N 5V pin can be left unconnected, since the Arduino
gets its power straight from the battery pack.

# 13. Common Ground

All components that communicate with the Arduino should share a common
electrical ground.

The main ground connections are:
```text
                 Arduino GND
                      │
                      │
HC-SR04 GND ──────────┼──────── L298N GND
                      │
                      │
                 Battery (-)
```
The common ground provides a shared voltage reference for the control signals.

Without a common ground, the Arduino's HIGH and LOW signals may not be
interpreted reliably by the L298N or sensor.

# 14. Complete Connection Tables
HC-SR04 Connections
| HC-SR04 Pin | Signal | Arduino Nano |
| ----------: | ------ | ------------ |
|           1 | VCC    | 5V           |
|           2 | TRIG   | D9           |
|           3 | ECHO   | D10          |
|           4 | GND    | GND          |

L298N → Arduino Connections
| L298N Pin | Function                | Arduino Nano |
| --------- | ----------------------- | ------------ |
| ENA       | Left motor speed (PWM)  | D5           |
| IN1       | Left motor direction 1  | D7           |
| IN2       | Left motor direction 2  | D8           |
| IN3       | Right motor direction 1 | D11          |
| IN4       | Right motor direction 2 | D12          |
| ENB       | Right motor speed (PWM) | D6           |

L298N Power Connections
| L298N Pin | Connection                                       |
| --------- | ------------------------------------------------ |
| +12V      | Battery positive through ON/OFF switch           |
| GND       | Battery negative/common ground                   |
| 5V        | Not used (Arduino powered separately via VIN)    |

L298N Motor Connections
| L298N Output | Motor              |
| ------------ | ------------------ |
| OUT1         | Left motor wire 1  |
| OUT2         | Left motor wire 2  |
| OUT3         | Right motor wire 1 |
| OUT4         | Right motor wire 2 |

Arduino Power Connections
| Arduino Pin | Connection                              |
| ----------- | ---------------------------------------- |
| VIN         | Battery positive through ON/OFF switch   |
| GND         | Battery negative/common ground           |

# 15. Complete Pin Map

For quick reference:
```text
                    ARDUINO NANO
                    ============

HC-SR04
D9  ──────────────── TRIG
D10 ──────────────── ECHO
5V  ──────────────── VCC
GND ──────────────── GND


L298N
D5  ──────────────── ENA
D7  ──────────────── IN1
D8  ──────────────── IN2

D11 ──────────────── IN3
D12 ──────────────── IN4
D6  ──────────────── ENB


POWER
VIN ──────────────── Battery (+), through switch
GND ──────────────── Common ground / Battery (-)
```
# 16. Complete Power Flow

The overall power arrangement can be represented as:
```text
              2S 18650 Battery Pack
                    +      -
                    │      │
                    │      └───────────────┐
                    │                      │
                 ON/OFF                    │
                  Switch                   │
                    │                      │
                    ├──────────────┐       │
                    │              │       │
                    ▼              ▼       ▼
                 L298N       Arduino VIN  Common
              Motor Supply                Ground
                    │
                    ▼
              DC Motors
```
The battery pack, through the switch, feeds both the L298N motor supply and
the Arduino VIN pin in parallel, so both sections power up and shut down
together.

# 17. How the Complete System Works
Step 1 — Detect an obstacle

The Arduino sends a trigger signal:
```text
Arduino D9
     ↓
HC-SR04 TRIG
```
The HC-SR04 measures the reflected ultrasonic signal.

The echo signal returns through:
```text
HC-SR04 ECHO
     ↓
Arduino D10
```
Step 2 — Calculate distance

The Arduino calculates the approximate distance.

For example:
```text
Distance > threshold
        ↓
No obstacle detected
        ↓
Move forward
```
If:
```text
Distance < Threshold
        ↓
Obstacle detected
        ↓
Stop/turn
```
Step 3 — Control the L298N

The Arduino sends motor-direction signals:
```text
D7  → IN1
D8  → IN2


D11 → IN3
D12 → IN4
```
It controls motor speed using:
```
D5 → ENA
D6 → ENB
```
Step 4 — L298N drives the motors

The L298N receives the control signals from the Arduino and drives the two
DC motors.
```
Arduino
   │
   │ Control signals
   ▼
L298N
   │
   │ Motor power
   ▼
DC Motors
```
# 18. Example Movement Logic

The exact movement algorithm will be implemented in software, but the basic
movement concepts are:

Move forward
```
Left motor  → Forward
Right motor → Forward
```
Turn left
```
Left motor  → Stop/slow
Right motor → Forward
```
Turn right
```
Left motor  → Forward
Right motor → Stop/slow
```
Stop
```
Left motor  → Stop
Right motor → Stop
```

# 19. Schematic Organization

A clean schematic can be arranged like this:
```
┌─────────────────────────────────────────────────────────┐
│                    ARDUINO NANO                         │
│                                                         │
│  VIN ─────────────── Battery (+) through switch          │
│  GND ─────────────── Common ground                      │
│                                                         │
│  D9 ─────────────── HC-SR04 TRIG                        │
│  D10 ────────────── HC-SR04 ECHO                        │
│                                                         │
│  D5 ─────────────── L298N ENA                           │
│  D7 ─────────────── L298N IN1                           │
│  D8 ─────────────── L298N IN2                           │
│  D11 ────────────── L298N IN3                           │
│  D12 ────────────── L298N IN4                           │
│  D6 ─────────────── L298N ENB                           │
│                                                         │
└─────────────────────────────────────────────────────────┘

          │                            │
          ▼                            ▼

┌─────────────────┐             ┌─────────────────┐
│    HC-SR04      │             │     L298N       │
│                 │             │                 │
│ VCC  → +5V      │             │ OUT1 → Left M   │
│ GND  → GND      │             │ OUT2 → Left M   │
│ TRIG → D9       │             │ OUT3 → Right M  │
│ ECHO → D10      │             │ OUT4 → Right M  │
└─────────────────┘             └─────────────────┘
                                        │
                                        │
                                  ┌─────┴─────┐
                                  ▼           ▼
                               Left M      Right M


                    ┌────────────────────┐
                    │ 2S 18650 Battery   │
                    │     Pack + BMS     │
                    └─────────┬──────────┘
                              │
                           Switch
                              │
                    ┌─────────┴─────────┐
                    ▼                   ▼
              Motor Supply        Arduino VIN
```
# 20. Wiring Checklist

Before powering the car, check every connection.

## Wiring Checklist

### HC-SR04

- [ ] VCC → Arduino 5V
- [ ] GND → Common GND
- [ ] TRIG → D9
- [ ] ECHO → D10

### L298N

- [ ] ENA → D5
- [ ] IN1 → D7
- [ ] IN2 → D8
- [ ] IN3 → D11
- [ ] IN4 → D12
- [ ] ENB → D6

### Motors

- [ ] Left motor → OUT1 / OUT2
- [ ] Right motor → OUT3 / OUT4

### Battery

- [ ] 2S 18650 battery pack
- [ ] Battery positive → switch
- [ ] Switch output → L298N motor supply
- [ ] Switch output → Arduino VIN
- [ ] Battery negative → common GND (Arduino, L298N, HC-SR04)

### Final Checks

- [ ] Check battery polarity
- [ ] Check common ground
- [ ] Check for short circuits
- [ ] Check ENA/ENB jumper configuration
- [ ] Confirm Arduino VIN connection (not 5V pin) from battery
- [ ] Verify all connections against the wiring table
      
# 21. Important Notes

> [!IMPORTANT]
> **Note 1 — Common Ground:**  
> Arduino GND, HC-SR04 GND, L298N GND, and battery negative must share a
> common electrical reference.

> [!NOTE]
> **Note 2 — PWM:**  
> D5 and D6 are used for ENA and ENB because they support PWM, allowing
> software-controlled motor speed.

> [!IMPORTANT]
> **Note 3 — ENA/ENB Jumpers:**  
> Remove the ENA and ENB jumpers on the L298N module when Arduino PWM control
> is required.

> [!NOTE]
> **Note 4 — Motor Direction:**  
> If a motor rotates in the opposite direction, swap the two wires of that
> motor rather than changing the overall wiring scheme.

> [!NOTE]
> **Note 5 — L298N +12V:**  
> The `+12V` marking is the motor-supply input on the module. It does not
> necessarily mean that a 12 V battery is required.

> [!WARNING]
> **Note 6 — L298N 5V:**  
> Since the Arduino is powered directly from the battery via VIN, the L298N
> `5V` pin is not used in this build and should be left disconnected unless
> you specifically confirm it is a regulated 5 V output you intend to use
> instead.

> [!WARNING]
> **Note 7 — Battery:**  
> A 2 × 18650 series pack is approximately 7.4 V nominal and can reach
> approximately 8.4 V when fully charged. Use an appropriate protected/BMS
> battery pack and compatible charging system.

> [!IMPORTANT]
> **Note 8 — Arduino Power via VIN:**  
> Connect the battery's switched positive line to the Arduino's VIN pin,
> never directly to the 5V pin. VIN feeds the onboard regulator, which
> safely steps the ~7.4–8.4 V pack voltage down to 5 V logic power. Feeding
> that voltage directly into 5V bypasses the regulator and can damage the
> board.
