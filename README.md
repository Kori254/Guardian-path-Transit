# Guardian-path-Transit

Overview

This project integrates multiple sensors using an Arduino to monitor and retrieve data from:

    MPU6050 Accelerometer & Gyroscope for motion sensing.
    TinyGPS++ module for retrieving GPS coordinates.
    MFRC522 RFID module for scanning RFID cards.

The data from these sensors are read continuously and displayed via the serial monitor.
Hardware Components

    Arduino (or any compatible microcontroller).
    MPU6050 Accelerometer & Gyroscope.
    TinyGPS++ GPS Module.
    MFRC522 RFID Reader.
    RFID Cards for scanning.

Pin Configuration

    MPU6050 is connected via I2C (SDA, SCL).
    GPS is connected to hardware Serial 2 (TXD2: 17, RXD2: 16).
    RFID uses SPI interface, connected to pin 5 for SS.

Software Requirements

    Arduino IDE for compiling and uploading the code.
    The following libraries are required:
        Adafruit_MPU6050
        Adafruit_Sensor
        TinyGPS++
        MFRC522

Installation of Libraries

You can install these libraries using the Arduino Library Manager:

    Open Arduino IDE.
    Go to Sketch > Include Library > Manage Libraries.
    Search for and install the following libraries:
        Adafruit MPU6050
        Adafruit Unified Sensor
        TinyGPS++
        MFRC522

Wiring Diagram

    MPU6050:
        VCC → 3.3V
        GND → GND
        SDA → A4
        SCL → A5

    GPS Module:
        VCC → 3.3V or 5V (depending on module)
        GND → GND
        RX → Pin 16 (RXD2)
        TX → Pin 17 (TXD2)

    RFID Reader:
        SDA → Pin 5
        MOSI → Pin 23
        MISO → Pin 19
        SCK → Pin 18
        GND → GND
        RST → Pin 22

Code Overview
Initial Setup

In the setup() function, the following components are initialized:

    The MPU6050 for accelerometer and gyroscope readings.
    The GPS module to retrieve latitude, longitude, and speed.
    The RFID module to detect and read the UID of RFID cards.

Main Loop

The loop() function does the following:

    Accelerometer Data: Continuously fetches and prints X, Y, Z values from the gyroscope.
    GPS Data: Fetches and prints the latitude, longitude, and speed. If no GPS data is available, it waits for a signal.
    RFID Scanning: Continuously checks for the presence of an RFID card. If a card is detected, it prints the card's UID.
