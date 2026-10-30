# Smart Bike Helmet

An ESP32-based Smart Bike Helmet project designed to detect potential accidents, obtain the rider's GPS location, and send emergency SMS alerts.

## Project Overview

The Smart Bike Helmet uses an MPU6050 motion sensor to monitor acceleration. When the measured acceleration exceeds a predefined threshold, the system identifies a potential accident.

After detecting an accident, the ESP32 reads GPS coordinates and sends an emergency alert containing the location through an SMS API using a Wi-Fi connection.

## Features

- Accident detection using the MPU6050 sensor.
- GPS-based location tracking.
- Automatic emergency SMS alerts.
- ESP32-based embedded system.
- Google Maps location link in the emergency message.
- Configurable accident detection threshold.

## Hardware Components

- ESP32 Development Board
- MPU6050 Accelerometer and Gyroscope
- GPS Receiver
- Power Supply
- Connecting Wires

## Software and Technologies

- Arduino Framework
- PlatformIO
- C++
- Arduino IDE / Visual Studio Code
- TinyGPS++
- Adafruit MPU6050 Library
- Wi-Fi and HTTP Client
- SMS API

## Working Principle

1. The ESP32 initializes the MPU6050 sensor and GPS module.
2. The MPU6050 continuously measures acceleration.
3. The ESP32 calculates the total acceleration.
4. If the acceleration exceeds the configured threshold of 2.5 g, a potential accident is detected.
5. The system reads the GPS coordinates.
6. An emergency SMS containing a Google Maps location link is sent through the SMS API over Wi-Fi.

## Project Structure

```text
SMART_BIKE_HELMET/
│
├── include/
├── lib/
│   └── Adafruit_MPU6050/
├── src/
│   └── main.cpp
├── test/
├── platformio.ini
├── .gitignore
└── README.md
```

## Pin Configuration

| Component | ESP32 Pin |
|---|---|
| GPS RX | GPIO 16 |
| GPS TX | GPIO 17 |
| MPU6050 SDA | Default ESP32 I2C SDA |
| MPU6050 SCL | Default ESP32 I2C SCL |

## Important Notes

- A working Wi-Fi connection is required for sending SMS alerts through the configured API.
- Configure your own Wi-Fi credentials, SMS API key, and recipient number before running the firmware.
- Never publish actual passwords, API keys, or private phone numbers in a public repository.
- GPS location availability depends on receiving a valid GPS signal.
- This is an educational prototype and should not be considered a certified vehicle safety device.

## Author

**Anuj Magar**

GitHub: [Anuj-Magar](https://github.com/Anuj-Magar)