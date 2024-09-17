#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <UrlEncode.h>


MFRC522DriverPinSimple ss_pin(5); // Pin for the RFID reader
MFRC522DriverSPI driver{ss_pin};   // SPI driver for the RFID reader
MFRC522 reader{driver}; 

// Struct to hold GPS data
struct gpsDataStruct {
  double latitude;
  double longitude;
  double speed;
};

struct accDataStruct {
  double gyroX;
  double gyroY;
  double gyroZ;
};

//send whatsapp message "I allow callmebot to send me messages in order to get APIKey"
String phoneNumber = "+254714086394";
String apiKey = "1592379";



void setup() {
  Serial.begin(9600);
  // Initialize GPS sensor
  initializeSensors();
  initializeAcc();

  while (!Serial);       // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).
  
  reader.PCD_Init();  // Initialize the RFID reader.
  Serial.println(F("Reader initialized"));
  MFRC522Debug::PCD_DumpVersionToSerial(reader, Serial);  // Print reader version info.

}
void loop() {
  // --- Accelerometer data ---
  accDataStruct accData = getAccData();  // Get accelerometer data
  Serial.print("Gyro X: "); Serial.print(accData.gyroX);
  Serial.print(", Gyro Y: "); Serial.print(accData.gyroY);
  Serial.print(", Gyro Z: "); Serial.println(accData.gyroZ);

  // --- GPS data ---
  // Continuously check for updated GPS data
  // Get GPS data and print to Serial Monitor
  gpsDataStruct gpsData = getGpsData();

  // Print the GPS data to the Serial Monitor
  Serial.print("LAT: ");
  Serial.println(gpsData.latitude, 6);
  
  Serial.print("LONG: "); 
  Serial.println(gpsData.longitude, 6);
  
  Serial.print("SPEED (km/h): "); 
  Serial.println(gpsData.speed);


  // --- RFID data ---
  // Check if there's an RFID card present
  if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
    Serial.print("RFID UID: ");
    for (byte i = 0; i < reader.uid.size; i++) {
      Serial.print(reader.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(reader.uid.uidByte[i], HEX);
      sendMessage("Child has boarded the bus");
    }
    Serial.println();
    
    // Halt the card and stop encryption
    reader.PICC_HaltA();
    reader.PCD_StopCrypto1();
  } else {
    Serial.println("No RFID card detected");
  }

  // Add a delay for readability and to prevent overwhelming the serial monitor
  delay(1000);
}
