/*
  Simple_DHT - Library for comunication and data interpretation with DHT sensors.
  Created by Tilen Stermecki, Apr 2023.
  Released into the public domain.
*/

#include <dht.h>
DHT dht(A0); // data pin of DHT on A0
void setup() {
  Serial.begin(9600);
}

void loop() {
  dht.readSensor(); // read values from sensor
  if (dht.fail) { // if reading fails...
    Serial.println("Detected errors in transmition:\n - " + dht.errorVerbose()); // error occured
  } else {
    Serial.println("temp: " + (String)dht.temp + "°C");
	Serial.println("hum: " + (String)dht.hum + "%\n");
  }
  delay(2000);
}