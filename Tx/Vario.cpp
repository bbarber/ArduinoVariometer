
#include <Arduino.h>
#include "MS5607.h"
#include "Vario.h"

MS5607 MS5607;

// This will change based on weather
const float seaLevelPressure = 1016.1;

float startingAltitude;

void Vario::setup() {
  Serial.begin(9600);
  MS5607.begin();
  startingAltitude = getAltitudeAvg();
}

float Vario::getRelativeAltitude() {

  float relativeAltitudeSum = 0;
  int altitudeReadings = 10;
  
  for(int i = 0; i < altitudeReadings; i++) {
    float currentAltitude = getAltitude();
    float relativeAltitude =  currentAltitude - startingAltitude;
    relativeAltitudeSum += relativeAltitude;
  }
  
  float realtiveAltitudeAvg = relativeAltitudeSum / altitudeReadings;
  
  return realtiveAltitudeAvg;
}

float Vario::getAltitude() {
  
  float pressure = getPressure();
  float temperature = getTemperature();
  
  float altitude = 
  (
      (pow(seaLevelPressure / pressure, 1/5.257) - 1.0) 
     * (temperature + 273.15)
  ) / 0.0065;

  // In feet
  return altitude * 3.28084;
}

float Vario::getAltitudeAvg(void) {

  // Take many samples and return
  // the median to smooth out the results
  
  int readings = 10;
  float altitudes[readings];

  for(int i = 0; i < readings; i++) {
    altitudes[i] = getAltitude();
  }
  
  float median = altitudes[readings / 2];
  return median;
}

float Vario::getPressure() {

  // Take many samples and return
  // the median to smooth out the results
  
  int readings = 3;
  float pressures[readings];

  for(int i = 0; i < readings; i++) {
    pressures[i] = MS5607.getPressure();
  }
  
  float median = pressures[readings / 2];
  return median / 100.0;
}

float Vario::getTemperature() {

  // Take many samples and return
  // the median to smooth out the results
  
  int readings = 3;
  int temperatures[readings];

  for(int i = 0; i < readings; i++) {
    temperatures[i] = MS5607.getTemperature();
  }
  
  int median = temperatures[readings / 2];

  // In degC
  return median / 100.0;
}
