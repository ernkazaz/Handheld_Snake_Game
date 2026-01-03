# Hand-Controlled Snake Game on TM4C123GH6PM

This repository contains an embedded systems project developed for **EE447 Laboratory**, implementing a classic **Snake Game** on the **Texas Instruments Tiva C Series TM4C123GH6PM** microcontroller.

The game is controlled by hand movements using a 3-axis accelerometer, rendered on a Nokia 5110 LCD, and enhanced with real-time speed control, visual feedback, and audio effects.

---

## 🎮 Project Overview

The Snake game integrates multiple peripherals and communication protocols to demonstrate real-time embedded system design:

- **Hand-controlled movement** using an ADXL345 accelerometer
- **Graphical display** via Nokia 5110 LCD (SPI)
- **Dynamic speed control** using a potentiometer (ADC)
- **Visual feedback** using PWM-controlled LEDs
- **Audio feedback** using a timer-driven buzzer
- **Robust control logic** with fault-tolerant sensor handling

---

## 🧩 Hardware Components

| Component | Description |
|---------|------------|
| MCU | TM4C123GH6PM (Tiva C LaunchPad) |
| Display | Nokia 5110 LCD (PCD8544 controller) |
| Accelerometer | ADXL345 (3-Axis, I2C) |
| Potentiometer | Used for speed control (ADC0) |
| LEDs | On-board RGB LEDs |
| Buzzer | Active buzzer (Timer-based) |

---

## 🔌 Hardware Connections

- **Nokia 5110 LCD**: SSI0 (SPI) + GPIO  
- **ADXL345 Accelerometer**: I2C0 (PB2, PB3)  
- **Potentiometer**: ADC0 input (PE3)  
- **Green LED**: PWM (PF3)  
- **Buzzer**: GPIO PB6 + Timer0A  

---

## 🏗️ Software Architecture

The software follows a **Modular Layered Architecture**, separating hardware control from game logic to ensure responsiveness and reliability.

### Layers

- **Hardware Abstraction Layer (HAL)**
  - I2C (Accelerometer)
  - SSI/SPI (LCD)
  - ADC (Potentiometer – implemented in Assembly)
  - PWM (LED brightness)
  - Timer-based Buzzer

- **Game Engine**
  - Snake movement and body management
  - Collision detection
  - Apple generation
  - Score tracking

- **Control Logic**
  - Finite State Machine (MENU, GAME, GAME_OVER)
  - Sensor data interpretation
  - Speed control algorithm
  - Audio-visual feedback

---

## 🧠 Game Logic Highlights

- **Virtual Grid System**
  - Screen divided into a 21×12 grid
  - Each grid cell maps to a 4×4 pixel block

- **Movement Rules**
  - Snake body follows the head
  - 180-degree turns are prevented

- **Collision Detection**
  - Wall collision
  - Self collision

- **Scoring**
  - Score equals snake length
  - Stored and displayed after game over

---

## ⏱️ Speed Control Algorithm

The game speed is controlled using a potentiometer and mapped linearly:

