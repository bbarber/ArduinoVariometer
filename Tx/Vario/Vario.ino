#include "MS5611.h"

MS5611 MS5611;

void setup() {
  Serial.begin(9600);
  MS5611.begin();
}

void loop() {
  //Serial.println(MS5611.getTemperature());
  Serial.println(MS5611.getPressure() * .01);
  delay(100);
}
