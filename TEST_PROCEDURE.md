---


```md
# TEST PROCEDURE - C++ Device Monitor

## 1. Objective

The objective of this test procedure is to verify that the C++ Device Monitor:

- Accepts TCP connections
- Processes valid telemetry messages
- Rejects invalid or malformed messages
- Detects threshold violations
- Logs system activity correctly
- Returns appropriate responses to the client

---

## 2. Test Environment

- Operating System: macOS
- Language: C++
- Library: Boost.Asio
- Communication Protocol: TCP
- Port: 8081

---

## 3. Build Instructions

### Compile Server

```bash
clang++ -std=c++17 src/server.cpp src/parser.cpp src/logger.cpp -o build/server
```

Compile Client
clang++ -std=c++17 src/client.cpp -o build/client
Compile Parser Test
clang++ -std=c++17 tests/test_parser.cpp src/parser.cpp -o build/test_parser

## 4. Execution Steps

Step 1: Start Server
./build/server
Expected output:
Server is listening on port 8081...

Step 2: Run Client
Open a new terminal:
./build/client

Step 3: Run Parser Test
./build/test_parser
Expected output:
All parser tests passed.

## 5. Test Cases

Test Case 1: Valid Message Processing

Input
DEVICE:sensor1;TEMP:30;PRESSURE:100;STATUS:OK
Expected Result
Server parses data correctly
No warnings generated
Client receives:
ACK: data received

Test Case 2: High Temperature Alert

Input
DEVICE:sensor2;TEMP:38;PRESSURE:105;STATUS:OK
Expected Result
Server detects high temperature
Output:
WARNING: High temperature detected!
Client receives:
ACK: data received with alerts

Test Case 3: High Pressure Alert

Input
DEVICE:sensor3;TEMP:32;PRESSURE:115;STATUS:OK
Expected Result
Server detects high pressure
Output:
WARNING: High pressure detected!
Client receives:
ACK: data received with alerts

Test Case 4: Multiple Alerts

Input
DEVICE:sensor3;TEMP:40;PRESSURE:115;STATUS:OK
Expected Result
Both alerts triggered
Output:
WARNING: High temperature detected!
WARNING: High pressure detected!
Client receives:
ACK: data received with alerts

Test Case 5: Missing Field (Malformed Message)

Input
DEVICE:sensor1;TEMP:40;STATUS:OK
Expected Result
Server rejects message
Client receives:
ERROR: malformed device message

Test Case 6: Invalid Numeric Value

Input
DEVICE:sensor1;TEMP:abc;PRESSURE:113;STATUS:OK
Expected Result
Server detects invalid numeric input
Client receives:
ERROR: invalid numeric field

Test Case 7: Log Verification

Action
cat logs/device.log
Expected Result
Log file contains:
Timestamp
Raw message
Parsed data
Alerts (if any)

Test Case 8: Network Verification (tcpdump)

Command
sudo tcpdump -i lo0 port 8081 -A
Expected Result
Captured client message:
DEVICE:sensor3;TEMP:40;PRESSURE:115;STATUS:OK
Captured server response:
ACK: data received with alerts

## 6. Pass Criteria

The system passes all tests if:

All valid inputs are processed correctly

Invalid inputs are rejected

Alerts are triggered based on thresholds

Logs are written correctly

Network communication is verified

Parser test passes successfully

## 7. Conclusion

This test procedure validates the correctness, reliability, and robustness of the C++ Device Monitor system across normal and edge-case scenarios.
