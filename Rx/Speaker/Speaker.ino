
#include "PCM.h"
#include "PCM_ZERO.h"
#include "PCM_ONE.h"
#include "PCM_TWO.h"
#include "PCM_THREE.h"
#include "PCM_FOUR.h"
#include "PCM_FIVE.h"
#include "PCM_SIX.h"
#include "PCM_SEVEN.h"
#include "PCM_EIGHT.h"
#include "PCM_NINE.h"

#include <Wire.h>


const int beeper_pin = 8;
const int led_pin = 13;
const int receive_pin = 1;

void setup() {
  Wire.begin(8);                   // join i2c bus with address #8
  Wire.onReceive(speakAltitude);   // register event
  Serial.begin(9600);
}

void speakAltitude(int numBytes) {

  char altitudeBytes[numBytes];
  
  if(Wire.available()) {
    for(int i = 0; i < numBytes; i++) {
      altitudeBytes[i] = Wire.read();
      Serial.println(altitudeBytes[i]);
    }
  }

  // Convert char array back into integer
  altitudeBytes[numBytes] = '\0';
  int altitude = atoi(altitudeBytes);
  
  Serial.print("Altitude: ");
  Serial.println(altitude);

  String altitudeStr = String(altitude, DEC);
  for (int i = 0; i < altitudeStr.length(); i++) {
    char digit = altitudeStr[i];

    if (digit == '0') startPlayback(PCM_ZERO, sizeof(PCM_ZERO));
    if (digit == '1') startPlayback(PCM_ONE, sizeof(PCM_ONE));
    if (digit == '2') startPlayback(PCM_TWO, sizeof(PCM_TWO));
    if (digit == '3') startPlayback(PCM_THREE, sizeof(PCM_THREE));
    if (digit == '4') startPlayback(PCM_FOUR, sizeof(PCM_FOUR));
    if (digit == '5') startPlayback(PCM_FIVE, sizeof(PCM_FIVE));
    if (digit == '6') startPlayback(PCM_SIX, sizeof(PCM_SIX));
    if (digit == '7') startPlayback(PCM_SEVEN, sizeof(PCM_SEVEN));
    if (digit == '8') startPlayback(PCM_EIGHT, sizeof(PCM_EIGHT));
    if (digit == '9') startPlayback(PCM_NINE, sizeof(PCM_NINE));

    delay(1000);
  }
}


void loop() {
  delay(1000);
}



