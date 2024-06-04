#include "SERIAL_.h"

String inputString = "";
bool stringComplete = false;

void serialEvent()
{
  if (Serial.available() > 0)
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete = true;
    }
  }
}

void confronta_stringhe()
{
  stringComplete = false;

  String confronto = String(inputString);
  
  if (confronto.equals("11\n") == 1)
  {
    TEST_canbus();
  }
  else if (confronto.equals("12\n") == 1)
  {
    TEST_i2c();
  }
  else if (confronto.equals("13\n") == 1)
  {
    TEST_ssr();
  }
  else
  {
    if ((confronto.equals("\n") != 1) && (isValidMessage(confronto))) {
      Serial.println(".");
      Serial.println("[\"11\",\"12\",\"13\"]");
      Serial.println("");
    }
  }

  inputString = ""; // clear the string:
  stringComplete = false;
}

bool isValidMessage(String message) {
  for (unsigned int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    if (!isPrintable(c)) {
      return false; // Contains special character, not a valid message
    }
  }
  return true; // No special characters found, valid message
}

bool isPrintable(char c) {
  // Check if character is printable and not a special character
  // ASCII values 32 (space) to 126 (~) are printable characters
  return (c >= 32 && c <= 126);
}
