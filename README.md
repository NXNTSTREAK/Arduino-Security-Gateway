# Dual-Zone Directional Security Gateway

A small embedded systems project built on an Arduino Nano.

This project uses two different sensors to detect not only the presence of a person, but also the direction of movement. By combining an IR sensor and a PIR motion sensor, the system can determine whether someone is entering or exiting a monitored area.

The goal of this project was to explore finite state machines (FSMs), sensor integration, and real-time event handling in embedded systems.

---

## Overview

Unlike a single-sensor security system, this project relies on the order in which two sensors are triggered.

An entry is detected when the IR sensor is triggered first, followed by the PIR sensor.

An exit is detected when the PIR sensor is triggered first, followed by the IR sensor.

Using a finite state machine allows the system to remember previous events and ignore incomplete or incorrect trigger sequences.

### Key Characteristics

- Arduino Nano based
- Finite State Machine (FSM)
- Direction detection
- Dual sensor integration
- Real-time event handling
- Non-blocking state transitions
- Lightweight embedded implementation

---

## Hardware Requirements

- Arduino Nano (ATmega328P)
- Reflective IR Sensor
- HC-SR501 PIR Motion Sensor
- Breadboard
- Jumper wires
- USB cable for programming

---

## Wiring

| Component | Arduino Pin | Logic | Purpose |
|-----------|------------:|-------|---------|
| Reflective IR Sensor (OUT) | D2 | Active-Low | Doorway detection |
| PIR Motion Sensor (OUT) | D3 | Active-High | Room motion detection |
| IR Sensor VCC | 5V | - | Power |
| PIR Sensor VCC | 5V | - | Power |
| GND | GND | - | Ground |

---

## How It Works

The system is built around a simple finite state machine.

### IDLE

The system waits for the first sensor to trigger.

- IR triggered → transition to **DOOR_BROKEN**
- PIR triggered → transition to **ROOM_MOTION**

---

### DOOR_BROKEN

The IR sensor has been triggered first.

The system now waits for the PIR sensor.

If motion is detected, the sequence is classified as a **Valid Entry**.

---

### ROOM_MOTION

The PIR sensor has been triggered first.

The system now waits for the IR sensor.

If the IR beam is broken, the sequence is classified as a **Valid Exit**.

---

If a sequence starts but is never completed, the system simply returns to the idle state without logging an event.

---

## Firmware Design

The firmware is implemented using a Finite State Machine instead of relying on long blocking delays.

This approach makes the system easier to extend while providing more reliable handling of sensor events.

The project also handles two different sensor logic levels:

- Active-Low IR sensor
- Active-High PIR sensor

The firmware normalizes these signals before processing them through the state machine.

---

## Engineering Challenge

One of the biggest challenges was handling the HC-SR501 PIR sensor.

Unlike the IR sensor, the PIR module keeps its output HIGH for several seconds after motion has stopped because of its built-in hardware latch.

This caused the system to immediately detect another motion event after resetting back to the idle state.

### Solution

Instead of relying on arbitrary `delay()` calls, the firmware waits until the PIR output returns LOW before allowing the state machine to reset.

This ensures that each detection cycle begins with both sensors in a known state and prevents repeated triggers caused by the PIR module's hardware latch.

---

## Concepts Demonstrated

This project helped me gain practical experience with:

- Embedded systems programming
- Finite State Machines (FSM)
- Sensor interfacing
- Mixed logic-level handling
- Real-time event processing
- State-based software design
- Arduino programming

---

## Future Improvements

Possible improvements include:

- LCD or OLED status display
- Event counter
- EEPROM logging
- Buzzer and LED indicators
- Wireless notifications
- Adjustable timeout handling
- Additional sensor zones

---

## License

This project is open for experimentation and learning.

Feel free to modify it, extend it, or use it as a reference for similar embedded systems projects.
