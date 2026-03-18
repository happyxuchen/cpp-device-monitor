# C++ Device Monitor

A lightweight C++ device communication and monitoring system built with Boost.Asio.

## Overview

This project simulates an industrial device monitoring workflow using a TCP client-server architecture.

The client sends structured telemetry messages containing device ID, temperature, pressure, and status.  
The server receives the message, validates required fields, safely parses numeric values, logs the event, and triggers warning alerts when thresholds are exceeded.

This project was designed to demonstrate core software engineering skills relevant to industrial and engineering systems, including C++ development, socket communication, modular design, secure input handling, logging, and basic testing.

## Features

- TCP client-server communication using Boost.Asio
- Modular parser and logger components
- Structured industrial-style telemetry format
- Continuous multi-device simulation
- Threshold-based alert detection
- Defensive parsing and input validation
- Log file generation
- Basic parser unit testing

## Message Format

```text
DEVICE:sensor1;TEMP:40;PRESSURE:113;STATUS:OK
```
