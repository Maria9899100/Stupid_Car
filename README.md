# Stupid_Car
# Obstacle-avoiding car


An autonomous obstacle-avoiding robot car built using an Arduino Nano. The robot detects obstacles using an ultrasonic distance sensor and navigates around them by making intelligent movement decisions without human intervention.

---

## Features

* Autonomous obstacle detection
* Real-time obstacle avoidance
* Forward, backward, left, and right movement
* Distance measurement using an ultrasonic sensor
* Modular firmware architecture
* Easily extendable for future enhancements

---

## Hardware

| Component           | Description                |
| ------------------- | -------------------------- |
| Arduino Nano        | Main microcontroller       |
| HC-SR04             | Ultrasonic distance sensor |
| L298N Motor Driver  | Controls the DC motors     |
| 2 × DC Gear Motors  | Robot movement             |
| Robot Chassis       | Mechanical platform        |
| Wheels              | Mobility                   |
| Li-ion Battery Pack | Power source               |
| Power Switch        | On/Off control             |

---

## Software

* C++
* PlatformIO
* Visual Studio Code

---

## Project Structure

text
.
├── docs/
│   ├── images/
│   ├── wiring_diagram.png
│   └── architecture.md
│
├── firmware/
│   ├── src/
│   ├── include/
│   ├── lib/
│   ├── test/
│   └── platformio.ini
│
├── media/
│   ├── demo.gif
│   └── demo.mp4
│
├── README.md
├── LICENSE
└── .gitignore


---

## How It Works

1. The ultrasonic sensor continuously measures the distance in front of the robot.
2. If no obstacle is detected within the configured threshold, the robot moves forward.
3. When an obstacle is detected:

   * The robot stops.
   * Measures available space.
   * Chooses a clear direction.
   * Turns accordingly.
   * Continues moving forward.

---

## Build and Upload

### Requirements

* Visual Studio Code
* PlatformIO Extension
* Arduino Nano

Clone the repository:

```bash
git clone https://github.com/your-username/obstacle-avoiding-robot.git
```

Open the project in VS Code and upload the firmware using PlatformIO.

---

## Future Improvements

* Servo-mounted ultrasonic sensor for wider scanning
* PID-based motor speed control
* Bluetooth manual control
* Wi-Fi remote control
* OLED status display
* Battery voltage monitoring
* IR obstacle sensors
* Line-following mode
* Encoder-based odometry
* Path planning algorithms
* ROS2 integration

---

## Learning Objectives

This project demonstrates knowledge of:

* Embedded Systems Programming
* C++
* Arduino Development
* Sensor Interfacing
* Motor Control
* PWM
* GPIO
* Software Modularity
* Basic Robotics
* Real-Time Programming

---

## Repository Status

🚧 Work in Progress

The project is actively under development. Features and documentation will continue to improve as the robot evolves.

---

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

## Author

**Maria Sultana**

If you find this project interesting, feel free to star the repository or open an issue with suggestions or improvements.
