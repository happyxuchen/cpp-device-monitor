# C++ Device Monitor

A TCP-based device monitoring system built in C++ using Boost.Asio.  
This project simulates industrial telemetry communication with structured data parsing, alert detection, logging, and network-level validation.

---

## 🚀 Overview

The C++ Device Monitor is a lightweight client-server system designed to simulate real-world device communication workflows.

The system:

- Receives structured telemetry data over TCP
- Parses and validates incoming messages
- Detects abnormal conditions (temperature / pressure)
- Logs all events with timestamps
- Returns acknowledgment responses to clients
- Verifies network communication using packet inspection tools

---

## 🏗️ Architecture

```text
Client  →  TCP Socket  →  Server
                         ↓
                  Data Parsing Module
                         ↓
                  Validation & Alerts
                         ↓
                      Logging
📦 Features

TCP client-server communication using Boost.Asio

Structured telemetry format (industrial-style)

Modular design (parser + logger separation)

Defensive input validation (malformed + invalid data)

Threshold-based alert detection

Persistent logging to file

Multi-device simulation (client sends multiple sensors)

Network validation using tcpdump (packet inspection)

Basic unit testing for parser module

📡 Message Format
DEVICE:sensor1;TEMP:40;PRESSURE:113;STATUS:OK
⚠️ Alert Rules
Parameter	Condition	Alert
TEMP	> 35	High temperature detected
PRESSURE	> 110	High pressure detected
📁 Project Structure
cpp-device-monitor/
├── include/           # Header files (parser, logger)
├── src/               # Core implementation
├── tests/             # Unit tests
├── logs/              # Output logs
├── build/             # Compiled binaries (ignored)
├── SPEC.md            # System specification
├── TEST_PROCEDURE.md  # Test procedures
└── README.md
🛠️ Build Instructions
Compile Server
clang++ -std=c++17 src/server.cpp src/parser.cpp src/logger.cpp -o build/server
Compile Client
clang++ -std=c++17 src/client.cpp -o build/client
Compile Tests
clang++ -std=c++17 tests/test_parser.cpp src/parser.cpp -o build/test_parser
▶️ Run

Start server:

./build/server

Run client (in another terminal):

./build/client

Run parser test:

./build/test_parser
🧪 Testing

The system is validated through:

Functional test cases (valid + invalid input)

Threshold-based alert testing

Log verification

Unit testing (parser module)

Network-level validation using tcpdump

See full details in:

TEST_PROCEDURE.md
🌐 Network Validation (Key Highlight)

TCP communication was verified using packet inspection on the loopback interface.

Example command:

sudo tcpdump -i lo0 port 8081 -A

Captured results confirm:

DEVICE:sensor3;TEMP:40;PRESSURE:115;STATUS:OK
ACK: data received with alerts

This demonstrates successful end-to-end communication and alert handling.

📊 Sample Output
Client
Sent: DEVICE:sensor1;TEMP:40;PRESSURE:113;STATUS:OK
Server reply: ACK: data received with alerts
Server
Parsed Data:
  DEVICE   = sensor1
  TEMP     = 40
  PRESSURE = 113
  STATUS   = OK

WARNING: High temperature detected!
WARNING: High pressure detected!
🔐 Engineering Highlights

Designed a modular C++ system with clear separation of concerns (parsing, logging, networking)

Implemented defensive programming to handle malformed and unsafe inputs

Simulated industrial telemetry communication using TCP sockets

Applied threshold-based monitoring logic to emulate real-world alert systems

Verified network communication using packet inspection tools (tcpdump)

Developed unit tests to validate parsing logic

⚙️ Future Improvements

Asynchronous server (Boost.Asio async model)

Multi-client concurrency

Configurable thresholds (config file / JSON)

Integration with industrial protocols (Modbus / OPC-UA)

Monitoring dashboard (Web UI)

Secure communication (TLS)
