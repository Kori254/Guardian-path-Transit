#include <TinyGPS++.h>

// Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600

// The TinyGPS++ object
TinyGPSPlus gps;

// Create an instance of the HardwareSerial class for Serial 2
HardwareSerial gpsSerial(2);


// Function to initialize the GPS sensor
void initializeSensors(){
  // Start the serial monitor
  Serial.begin(9600);

  // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 started at 9600 baud rate");
}

// Function to get GPS data and return it as a gpsDataStruct struct
gpsDataStruct getGpsData(){
  gpsDataStruct data;
  
  // Set initial values in case GPS data isn't available
  data.latitude = 0.0;
  data.longitude = 0.0;
  data.speed = 0.0;

  unsigned long start = millis();
  bool newData = false;

  // Try to gather GPS data for a few seconds (e.g., 2000 ms)
  while (millis() - start < 2000) {
    // Check if data is available from the GPS module
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        newData = true;
      }
    }

    // If new data has been received, store it in the struct and break the loop
    if (newData && gps.location.isUpdated()) {
      data.latitude = gps.location.lat();
      data.longitude = gps.location.lng();
      data.speed = gps.speed.kmph(); // Get speed in km/h
      break;  // Exit the loop if valid data is received
    }
  }

  // If no valid data was received, print a message
  if (!newData) {
    Serial.println("No GPS data available. Trying again...");
  }

  return data;
}