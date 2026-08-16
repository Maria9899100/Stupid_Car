## 3-Pin Slide Switch — Pin Configuration (Arduino Nano)

A 3-pin slide switch is typically an **SPDT (Single Pole, Double Throw)** switch — one common pin and two output pins. Sliding it connects the common to one side or the other.

| Pin | Function |
|---|---|
| **Common (C)** — usually the middle pin | Connects to whichever side the slider is pushed toward |
| **Pin 1 (left/top)** | Connected to Common when slider is in Position 1 |
| **Pin 2 (right/bottom)** | Connected to Common when slider is in Position 2 |

Only **one side is connected at a time** — either Common↔Pin1 or Common↔Pin2, never both (unlike a 2-pin switch, there's no "off" middle state on most 3-pin sliders).

### Option A: Digital Input (selecting between two states)

Common → Nano digital pin (e.g., D8), with a pull-down resistor to GND
Pin 1 → Nano 5V
Pin 2 → (leave unconnected, or wire to GND for a defined LOW state)

Reads `HIGH` in one position, `LOW` (via pull-down) in the other.

### Option B: Power Switch (cutting power to a circuit)

Common → Battery positive (+)
Pin 1 → Circuit VCC (power ON position)
Pin 2 → Unconnected (power OFF position)

Classic use case — many battery packs use a 3-pin slide switch this way even though only 2 pins are actively used.

**Notes:**
- For a clean digital read, use a **pull-down resistor** (~10kΩ) from the input pin to GND, or use `INPUT_PULLUP` mode and wire the switch to pull the pin to GND instead — this avoids a "floating" pin when reading state.
- Some 3-pin slide switches are **SPDT ON-ON**, while others are **ON-OFF-ON** (with a middle neutral spot) — check your specific switch's datasheet, since wiring intent differs slightly.
- Middle pin being "Common" is standard, but always verify with a multimeter if unlabeled — some cheaper switches don't follow this convention.
