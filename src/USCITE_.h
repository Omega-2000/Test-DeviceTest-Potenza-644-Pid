#ifndef USCITE__H
#define USCITE__H

#include <Arduino.h>

#define SSR_1   22
#define SSR_2   23

extern String inputString_u;      // = "";        // a String to hold incoming data
extern bool stringComplete_u;     // = false;     // whether the string is complete
void serialEvent_u();

void BEGIN_ssr();
void TEST_ssr();


#endif