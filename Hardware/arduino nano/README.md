# Arduino Nano (ATmega328) — Pin Configuration Guide

A complete reference for every pin on the **Arduino Nano** board (ATmega328P microcontroller, old or new bootloader).

## 📌 Board Overview

| Spec | Value |
|---|---|
| Microcontroller | ATmega328P |
| Operating Voltage | 5V |
| Input Voltage (recommended) | 7–12V (via VIN) |
| Input Voltage (limit) | 6–20V |
| Digital I/O Pins | 22 (6 provide PWM output) |
| Analog Input Pins | 8 (A0–A7) |
| PWM Pins | D3, D5, D6, D9, D10, D11 |
| DC Current per I/O Pin | 40 mA |
| Flash Memory | 32 KB (2 KB used by bootloader) |
| SRAM | 2 KB |
| EEPROM | 1 KB |
| Clock Speed | 16 MHz |
| USB | Mini-B (older) / Micro-B (newer clones) |

---

## 🧭 Pinout Diagram (Text Layout)

The Nano has 30 pins total, arranged in two rows (15 per side) when viewed with the USB port facing left.

```
                     ┌─────────────────┐
              TX1 ●──┤ D1/TX      VIN  ├──● Power In (7-12V)
              RX0 ●──┤ D0/RX      GND  ├──● Ground
              RST ●──┤ RESET      RESET├──● Reset
              GND ●──┤ GND         5V  ├──● 5V Output
              D2  ●──┤ D2          A7  ├──● A7 (Analog only)
        PWM   D3  ●──┤ D3~         A6  ├──● A6 (Analog only)
              D4  ●──┤ D4          A5  ├──● A5 / SCL (I2C)
        PWM   D5  ●──┤ D5~         A4  ├──● A4 / SDA (I2C)
        PWM   D6  ●──┤ D6~         A3  ├──● A3
              D7  ●──┤ D7          A2  ├──● A2
              D8  ●──┤ D8          A1  ├──● A1
        PWM   D9  ●──┤ D9~         A0  ├──● A0
        PWM  D10  ●──┤ D10~       AREF ├──● Analog Reference
        PWM  D11  ●──┤ D11~       3V3  ├──● 3.3V Output
             D12  ●──┤ D12         D13 ├──● D13 / Onboard LED
                     │      USB        │
                     └─────────────────┘
```
> `~` next to a pin number means it supports **PWM** (analog-like output).

---

## 🔌 Full Pin Reference Table

### Digital Pins (D0–D13)

| Pin | Alt. Function | Notes |
|---|---|---|
| D0 | RX | Serial **Receive**. Used for UART communication. Avoid using while uploading code. |
| D1 | TX | Serial **Transmit**. Same caution as D0. |
| D2 | INT0 | External interrupt pin. |
| D3 | INT1, PWM | External interrupt + PWM output. |
| D4 | — | General purpose digital I/O. |
| D5 | PWM | PWM output. |
| D6 | PWM | PWM output. |
| D7 | — | General purpose digital I/O. |
| D8 | — | General purpose digital I/O. |
| D9 | PWM | PWM output. |
| D10 | PWM, SS | PWM output; SPI Slave Select. |
| D11 | PWM, MOSI | PWM output; SPI Master Out Slave In. |
| D12 | MISO | SPI Master In Slave Out. |
| D13 | SCK | SPI Clock. **Also connected to the onboard LED.** |

### Analog Pins (A0–A7)

| Pin | Alt. Function | Notes |
|---|---|---|
| A0 | D14 | Analog input; can also be used as digital pin. |
| A1 | D15 | Analog input; can also be used as digital pin. |
| A2 | D16 | Analog input; can also be used as digital pin. |
| A3 | D17 | Analog input; can also be used as digital pin. |
| A4 | D18, SDA | Analog input; **I2C Data line**. |
| A5 | D19, SCL | Analog input; **I2C Clock line**. |
| A6 | — | Analog **input only** (no digital function). |
| A7 | — | Analog **input only** (no digital function). |

### Power Pins

| Pin | Description |
|---|---|
| VIN | Input voltage when powering via an external source (7–12V recommended). Not regulated. |
| 5V | Regulated 5V output, or 5V input if powering via USB/5V pin directly. |
| 3V3 | Regulated 3.3V output (max ~50 mA draw). Useful for 3.3V sensors/modules. |
| GND | Ground. Multiple GND pins available — use whichever is convenient. |
| RESET | Pull LOW to reset the microcontroller. |
| AREF | Analog reference voltage for `analogRead()` — used with `analogReference()`. |

---

## ⚙️ Special/Shared Functions Summary

| Function | Pin(s) |
|---|---|
| PWM (analogWrite) | D3, D5, D6, D9, D10, D11 |
| I2C (Wire library) | A4 (SDA), A5 (SCL) |
| SPI | D10 (SS), D11 (MOSI), D12 (MISO), D13 (SCK) |
| UART (Serial) | D0 (RX), D1 (TX) |
| External Interrupts | D2 (INT0), D3 (INT1) |
| Onboard LED | D13 |

---

## ⚠️ Important Notes & Best Practices

- **Max current per pin:** 40 mA (20 mA recommended for safety). Never exceed this — use a transistor/MOSFET driver for motors, relays, or high-current loads.
- **Total current across all I/O pins:** should not exceed ~200 mA.
- **A6 & A7** are analog-input-only — they **cannot** be used as digital I/O, unlike A0–A5.
- **D0/D1 (RX/TX)** are used during code upload — disconnect anything wired to them before flashing new code, or you may get upload errors.
- **AREF** should never be connected directly to a voltage source without first calling `analogReference(EXTERNAL)` in code — doing so can damage the ATmega328.
- The **3.3V pin** is NOT meant to power high-current devices; it's derived from the 5V line through a small regulator.
- Two Nano hardware revisions exist: **Old Bootloader** and **New Bootloader** — if your Nano doesn't upload code, try switching the "Processor" option in the Arduino IDE (`Tools > Processor > ATmega328P (Old Bootloader)`).

---

## 🧩 Quick Wiring Examples

**I2C Sensor (e.g., OLED, MPU6050):**
```
Sensor SDA → A4
Sensor SCL → A5
Sensor VCC → 5V (or 3.3V, check sensor spec)
Sensor GND → GND
```

**Servo Motor:**
```
Signal → any PWM pin (D3, D5, D6, D9, D10, D11)
VCC    → 5V (or external supply for high-torque servos)
GND    → GND (common ground with Nano)
```

**SPI Device (e.g., SD card module):**
```
CS/SS → D10
MOSI  → D11
MISO  → D12
SCK   → D13
```

**Motor Driver (e.g., L298N / L293D):**

| Motor Driver Pin | Connect To | Purpose |
|---|---|---|
| IN1, IN2 | Any digital pins (e.g., D7, D8) | Direction control for Motor A |
| IN3, IN4 | Any digital pins (e.g., D4, D2) | Direction control for Motor B |
| ENA | A **PWM** pin (D3, D5, D6, D9, D10, D11) | Speed control for Motor A |
| ENB | A **PWM** pin (D3, D5, D6, D9, D10, D11) | Speed control for Motor B |
| GND | Nano GND | Common ground — must be shared between Nano and driver |
| 5V (logic) | Nano 5V (only if driver needs logic power separately) | Powers the driver's logic chip |
| VCC / VM (motor power) | **External battery/supply**, NOT the Nano's 5V or VIN | Motors draw far more current than the Nano can safely supply |

```
Nano D9  (PWM) → ENA
Nano D7        → IN1
Nano D8        → IN2
Nano D10 (PWM) → ENB
Nano D4        → IN3
Nano D2        → IN4
Nano GND       → L298N GND (and battery GND)
Battery +      → L298N VCC/VM
```

> ⚠️ **Never power motors directly from the Nano's 5V or VIN pin.** Motors can pull far more current than the Nano's regulator or USB port can handle — use a separate battery/supply for the driver's motor-power input, and always tie the grounds together.

---

## 📚 References

- [Arduino Nano Official Documentation](https://docs.arduino.cc/hardware/nano)
- [ATmega328P Datasheet (Microchip)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

---

*Feel free to fork/edit this README for your own project's wiring documentation.*
