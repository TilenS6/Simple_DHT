/*
  Simple_DHT.cpp - Library for comunication and data interpretation with DHT sensors.
  Created by Tilen Stermecki, Apr 2023.
  Released into the public domain.
*/

#ifndef DHT_H
#define DHT_H
#include <Arduino.h>

class DHT {
    byte pin;
	String errorLookup[3]= {"", "Error while checking for data validation. Low quality data recieved.", "Device didn't respond. Check wiring."};
  public:
    float temp, hum;
    uint8_t fail;
	
    DHT(byte);
    void readSensor();
	String errorVerbose();
};

#endif