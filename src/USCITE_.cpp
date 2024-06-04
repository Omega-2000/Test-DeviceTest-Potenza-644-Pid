#include "USCITE_.h"

String inputString_u = "";
bool stringComplete_u = false;

void serialEvent_u() {
  while (Serial.available())
  {
    char inChar = (char)Serial.read(); // get the new byte:
    inputString_u += inChar;             // add it to the inputString:
    if (inChar == '\n')
    { // if the incoming character is a newline, set a flag so the main loop cando something about it:
      stringComplete_u = true;
    }
  }
}

void BEGIN_ssr() {
    pinMode(SSR_1, OUTPUT);
    pinMode(SSR_2, OUTPUT);
}

void TEST_ssr() {
    Serial.println("");
    Serial.println("TEST SSR");


    //  SSR_1
    Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede lampeggiare il led D5 'SSR_1', oppure cliccare su 'NO' se il led non lampeggia\"}");
    //  DA SPECIFICARE DOVE

    unsigned long t_ssr = 0;
    bool next = 0;
    while (!next) {
        //  BLINK
        if ((millis() - t_ssr) > 1000) {
            digitalWrite(SSR_1, !digitalRead(SSR_1));
            t_ssr = millis();
        }

        //  ASPETTA NEXT E TEST SSR2
        serialEvent_u();
        if (stringComplete_u)
        {
            stringComplete_u = false;
            String confronto = String(inputString_u);
            //Serial.println(confronto);
            //Serial.println("");
            if (confronto.equals("98\n") == 1) {
                next = 1;
                Serial.println("next");
            } else {
                Serial.println("");
                Serial.println("Inviare il comando '98' per passare al test successivo");
                Serial.println("");
            }
            inputString_u = ""; // clear the string:
            stringComplete_u = false;
            //Serial.println("");
            //Serial.println("In attesa...");
        }

        delay(10);
    }
    digitalWrite(SSR_1, 0);


    //  SSR_2
    Serial.println("{\"name\":\"description\",\"value\":\"Cliccare su 'SI' se si vede lampeggiare il led D6 'SSR_2', oppure cliccare su 'NO' se il led non lampeggia\"}");
    //  DA SPECIFICARE DOVE

    next = 0;
    while (!next) {
        //  BLINK
        if ((millis() - t_ssr) > 1000) {
            digitalWrite(SSR_2, !digitalRead(SSR_2));
            t_ssr = millis();
        }

        //  ASPETTA NEXT E TEST SSR2
        serialEvent_u();
        if (stringComplete_u)
        {
            stringComplete_u = false;
            String confronto = String(inputString_u);
            //Serial.println(confronto);
            //Serial.println("");
            if (confronto.equals("99\n") == 1) {
                next = 1;
                Serial.println("end");
            } else {
                Serial.println("");
                Serial.println("Inviare il comando '99' per completare il test");
                Serial.println("");
            }
            inputString_u = ""; // clear the string:
            stringComplete_u = false;
            //Serial.println("");
            //Serial.println("In attesa...");
        }

        delay(10);
    }
    digitalWrite(SSR_2, 0);


    Serial.println("");
    Serial.println("FINE TEST SSR");
    Serial.println("");
}
