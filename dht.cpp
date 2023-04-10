/*
  Simple_DHT.cpp - Library for comunication and data interpretation with DHT sensors.
  Created by Tilen Stermecki, Apr 2023.
  Released into the public domain.
*/

#ifndef DHT_CPP
#define DHT_CPP

#include "dht.h"
DHT::DHT(byte DHT_PIN) {
  pin = DHT_PIN;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
  fail = false;
}
void DHT::readSensor() {
  byte data[5];
  digitalWrite(pin, 0);
  delayMicroseconds(1000);
  digitalWrite(pin, 1);
  delayMicroseconds(30);

  pinMode(pin, INPUT);
  delayMicroseconds(10);
  // while (digitalRead(pin));
  uint8_t timeout = 1;
  while (!digitalRead(pin) && timeout != 0) {
    ++timeout;
  }
  if (timeout == 0) { // most of the time comes to ~19 (Arduino UNO R3, this is very bad method, I know)
    fail = 2;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, 1);
    return;
  }

  for (byte dat = 0; dat < 5; dat++) {
    data[dat] = 0;
    for (byte i = 0; i < 8; i++) {
      unsigned long t = pulseIn(pin, HIGH, 10000UL);
      if (t == 0) {
        fail = 2;
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 1);
        return;
      }
      data[dat] |= (t > 50) << (7 - i);
    }
  }
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);

  uint8_t tmp = 0;
  for (byte i = 0; i < 4; i++)
    tmp += data[i];

  if (tmp == data[4]) {
    fail = 0;
    hum = (float)(((uint16_t)(data[0] & 0b01111111) << 8) | data[1]) / 10.0;
    if (data[0] & 0b10000000) hum *= -1;
    temp = (float)(((uint16_t)(data[2] & 0b01111111) << 8) | data[3]) / 10.0;
    if (data[2] & 0b10000000) temp *= -1;
  } else {
    fail = 1;
  }
}

String DHT::errorVerbose() {
  return errorLookup[fail];
}

#endif