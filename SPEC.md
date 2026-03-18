# SPECIFICATION - C++ Device Monitor

## 1. Purpose

The C++ Device Monitor is a lightweight industrial-style telemetry monitoring system built using a TCP client-server architecture.

The system simulates real-world device communication by receiving structured messages, validating and parsing telemetry data, detecting abnormal conditions, and logging system activity.

---

## 2. System Overview

The system consists of:

- **Client**: Sends device telemetry data over TCP
- **Server**: Receives, validates, parses, analyzes, and logs the data
- **Parser Module**: Extracts structured data from raw messages
- **Logger Module**: Writes processed data and alerts to a log file

---

## 3. Message Format

The client sends messages in the following format:

```text
DEVICE:sensor1;TEMP:40;PRESSURE:113;STATUS:OK
```

---

## 4. Required Fields

Each message must include the following fields:

DEVICE

TEMP

PRESSURE

STATUS

If any field is missing, the message is considered invalid.

## 5. Input Validation Rules

5.1 Field Validation

All required fields must be present

Fields must follow KEY:VALUE format

5.2 Numeric Validation

TEMP must be a valid integer

PRESSURE must be a valid integer

If validation fails, the server returns:

ERROR: malformed device message

or

ERROR: invalid numeric field

## 6. Alert Conditions

The server evaluates incoming data against predefined thresholds:

Parameter Condition Alert
TEMP > 35 High temperature detected
PRESSURE > 110 High pressure detected

Multiple alerts may be triggered simultaneously.

## 7. Server Responses

The server responds with one of the following:

ACK: data received

ACK: data received with alerts

ERROR: malformed device message

ERROR: invalid numeric field

## 8. Logging

All processed messages are recorded in:

logs/device.log

Each log entry includes:

Timestamp

Raw message

Parsed values

Alert messages (if any)

## 9. Network Configuration

Protocol: TCP

Port: 8081

Interface: localhost (127.0.0.1)

## 10. System Limitations

Supports only localhost communication

Uses synchronous socket processing

Handles one client request per connection

Threshold values are hardcoded

No authentication or encryption

## 11. Future Improvements

Asynchronous communication using Boost.Asio

Configurable thresholds via external config file

Multi-client concurrent handling

Secure communication (TLS)

Integration with industrial protocols (Modbus/OPC)

Advanced monitoring dashboard
