#include "I2C_.h"

void TEST_i2c() {
  Serial.println("");
  Serial.println("TEST I2C");

  byte error, address;
  int nDevices = 0;
  bool foundTarget_1 = false;
  bool foundTarget_2 = false;

  const char* deviceNames[2] = { "SENSORE1" , "SENSORE2"};
  int targetDevices[2] = { 0x5A , 0x5B};

  Serial.println("Scanning for I2C devices ...");

  // Scan I2C addresses from 1 to 127
  for (address = 1; address < 127; address++) {
    // Start communication with the I2C address
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    // Check for acknowledgment
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      // Check if the found address matches the target device address
      if (address == targetDevices[0]) foundTarget_1 = true;
      if (address == targetDevices[1]) foundTarget_2 = true;

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
    delay(10);
  }

  

  // Check if the target device (0x50) was not found
  //if /*(*/(nDevices == 1)/* && (!foundTarget_1 || !foundTarget_2))*/ {
  /*if (nDevices == 1) {

    char errorMessage[256] = "";
    strcpy(errorMessage, "Missing Devices:");

    // Aggiungi il valore di targetDevices[0] al messaggio
    char buffer[16];

    if (!foundTarget_1) sprintf(buffer, "%d ERRORE i2c ---> ", targetDevices[0]); else if (!foundTarget_2) sprintf(buffer, "%d ERRORE i2c ---> ", targetDevices[1]);
    
    strcat(errorMessage, buffer);

    // Aggiungi il valore di deviceNames[0] al messaggio
    if (!foundTarget_1) strcat(errorMessage, deviceNames[0]); else if (!foundTarget_2) strcat(errorMessage, deviceNames[0]);
    Serial.print("{ \"name\": \"!I2C\", \"result\": \"error\", \"error\": \"");
    Serial.print(errorMessage);
    Serial.print(" errorMessage\"}\n");
  }*/

  //  If both I2C devices found
  if (foundTarget_1 && foundTarget_2) {

    Serial.println("Test OK");
    Serial.println("{ \"name\": \"I2C PID\", \"result\": \"ok\"}");

  } else if (foundTarget_1 || foundTarget_2) {

    Serial.println("Test ERROR");
    if (foundTarget_1) Serial.println("{ \"name\": \"I2C PID\", \"result\": \"error\", \"error\":\"Il sensore di temperatura 2 (0x5B) non trovato\"");
    else if (foundTarget_2) Serial.println("{ \"name\": \"I2C PID\", \"result\": \"error\", \"error\":\"Il sensore di temperatura 1 (0x5A) non trovato\"");
    
  } else if (!foundTarget_1 && !foundTarget_2) {
    
    Serial.println("Test ERROR");
    Serial.println("{ \"name\": \"I2C PID\", \"result\": \"error\", \"error\":\"Non è stato trovato nessun sensore\"");
  }

  // If no I2C devices found, print a message
  /*if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }*/

  Serial.println("");
  Serial.println("FINE TEST I2C");
  Serial.println("");
}
