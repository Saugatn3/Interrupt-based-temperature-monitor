# ESP32 Interrupt-Based Temperature Monitor

A project using the ESP32 hardware timer and ADC to periodically sample temperature in a non-blocking manner. The sampling rate can be changed dynamically using a GPIO interrupt.

---

## Overview

This project demonstrates how to use ESP32 hardware timers and interrupts for precise periodic tasks without using blocking delays. A temperature sensor is sampled at fixed intervals, and the data is transmitted over UART for debugging and monitoring.

---

## How It Works

- A hardware timer is configured with 1 µs resolution using a prescaler.
- The timer generates periodic interrupts at predefined intervals.
- The timer ISR sets a flag indicating it is time to sample temperature.
- The main loop reads the ADC, converts the value to temperature, and sends the data over UART.
- A button interrupt cycles through different sampling intervals (1s, 500ms, 200ms).
- An LED turns ON when the temperature crosses a defined threshold.
