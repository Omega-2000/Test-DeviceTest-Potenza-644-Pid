#ifndef CANBUS__H
#define CANBUS__H

#include <Arduino.h>
#include <SPI.h>
#include <CAN.h>

#define PIN_SPI_MISO 6//50
#define PIN_SPI_MOSI 5//51
#define PIN_SPI_SCK 7//52
#define MCP2515_DEFAULT_CS_PIN 4
#define MCP2515_DEFAULT_INT_PIN 11

//extern unsigned long t_canbus;

void TEST_canbus();

#endif
