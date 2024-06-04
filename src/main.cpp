#include "SERIAL_.h"

#define versione T1

void setup()
{
  Serial.begin(9600);

  BEGIN_ssr();

  while (!Serial)
    ;

  Wire.begin();

  inputString.reserve(200); // reserve 200 bytes for the inputString

  Serial.println("");
  Serial.println("[SETUP] In attesa...");
}

void loop()
{
  serialEvent();
  if (stringComplete)
  {
    confronta_stringhe();
    //Serial.println("");
    //Serial.println("In attesa...");
    return;
  }
}
