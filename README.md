# STM32 Ultrasonic Distance Meter

![Platform](https://img.shields.io/badge/STM32-F4-blue)
![Sensor](https://img.shields.io/badge/Sensor-HC--SR04-orange)

## 📝 Description
A simple embedded project based on **STM32F4** that measures distance using an ultrasonic sensor (HC-SR04) and displays the result on an LCD 1602.

The main goal of this project was to practice working with **Hardware Timers (Input Capture & PWM)** rather than using simple blocking delays.

## ⚙️ Key Features
* **Distance Measurement:** Uses `TIM3` in **Input Capture mode** to precisely measure the echo pulse width from the sensor.
* **Visual Output:** Displays calculated distance (in cm) on a 16x2 LCD.
* **Status LEDs:** Controls on-board LEDs using **PWM** (`TIM4`) to indicate system status.

## 🚀 How it works
1. **Trigger:** The MCU sends a 10µs pulse via PWM to the sensor.
2. **Echo:** The sensor responds with a pulse. The MCU captures the timestamp of the rising and falling edges using Timer Input Capture.
3. **Calculation:** The pulse duration is converted to distance using the formula: `Distance (cm) = Pulse_Width (µs) / 58`.
4. **Display:** The result is formatted and sent to the LCD.

## 📂 Project Structure
* `Src/main.c` - Main logic, timer handling, and distance calculation.
* `Src/MyLCDcode.c` - Low-level driver for LCD control (adapted for this project).
* `Src/tim.c` - Timer initialization code.
