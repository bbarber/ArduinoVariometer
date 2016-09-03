
#include "PCM.h"

#include "PCM_FIVE.h"
#include "PCM_TENS.h"
#include "PCM_HUNDREDS.h"

//#include <VirtualWire.h>


const int beeper_pin = 8;
const int led_pin = 13;
const int receive_pin = 11;

void setup() {
  //  delay(1000);
  Serial.begin(9600);
  //  Serial.println("setup");
  //  vw_set_rx_pin(receive_pin);
  //  vw_setup(2000);  // Bits per sec
  //  vw_rx_start();       // Start the receiver PLL running
}



void speakAltitude(int altitude) {

  // Limited to only 32kb of flash memory
  // so only have 20ft resolution and exclude
  // the other samples until I have a sd card

  // Sound an alarm if greater than 400ft
  if (altitude > 400) {
    tone(11, 400, 500); delay(500);
    tone(11, 200, 500); delay(500);
    tone(11, 400, 500); delay(500);
    tone(11, 200, 500); delay(500);
    tone(11, 400, 500); delay(500);
    tone(11, 200, 500); delay(500);
    return;
  }

  // Round up to nearest 20ft
  int ft = round(altitude / 20) * 20;
  int hundredFeet = ft / 100;
  int tensFeet = (ft % 100) / 10;

  if (hundredFeet == 1)  startPlayback(PCM_ONE_HUNDRED, sizeof(PCM_ONE_HUNDRED));
  if (hundredFeet == 2)  startPlayback(PCM_TWO_HUNDRED, sizeof(PCM_TWO_HUNDRED));
  if (hundredFeet == 3)  startPlayback(PCM_THREE_HUNDRED, sizeof(PCM_THREE_HUNDRED));
  //if(hundredFeet == 4)  startPlayback(PCM_FOUR_HUNDRED, sizeof(PCM_FOUR_HUNDRED));
  //if(hundredFeet == 5)  startPlayback(PCM_FIVE_HUNDRED, sizeof(PCM_FIVE_HUNDRED));
  delay(500);


  //if(tensFeet == 1) startPlayback(PCM_TEN, sizeof(PCM_TEN));
  if (tensFeet == 2) startPlayback(PCM_TWENTY, sizeof(PCM_TWENTY));
  //if(tensFeet == 3) startPlayback(PCM_THIRTY, sizeof(PCM_THIRTY));
  if (tensFeet == 4) startPlayback(PCM_FOURTY, sizeof(PCM_FOURTY));
  //if(tensFeet == 5) startPlayback(PCM_FIFTY, sizeof(PCM_FIFTY));
  if (tensFeet == 6) startPlayback(PCM_SIXTY, sizeof(PCM_SIXTY));
  //if(tensFeet == 7) startPlayback(PCM_SEVENTY, sizeof(PCM_SEVENTY));
  if (tensFeet == 8) startPlayback(PCM_EIGHTY, sizeof(PCM_EIGHTY));
  //if(tensFeet == 9) startPlayback(PCM_NINETY, sizeof(PCM_NINETY));


  delay(400);
  startPlayback(PCM_FEET, sizeof(PCM_FEET));
}


void loop() {
  for (int i = 1; i < 600; i += 5) {
    Serial.println(i);
    speakAltitude(i);
    delay(500);
  }

  //getAltitude();
  delay(3000);
}



//
//void getAltitude()
//{
//  uint8_t buf[VW_MAX_MESSAGE_LEN];
//  uint8_t buflen = VW_MAX_MESSAGE_LEN;
//
//  char message[4];
//
//  if (vw_get_message(buf, &buflen)) // Non-blocking
//  {
//    for (int i = 0; i < buflen; i++)
//    {
//      message[i] = char(buf[i]);
//    }
//
//    message[buflen] = '\0';
//    int altitude = atoi(message);
//
//    delay(10);
//    Serial.println(altitude);
//  }
//}
//

