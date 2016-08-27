#include "pitches.h"

#include <VirtualWire.h>


const int beeper_pin = 8;
const int led_pin = 13;
const int receive_pin = 11;

void setup()
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("setup");
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  char message[4];

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    for (int i = 0; i < buflen; i++)
    {
      message[i] = char(buf[i]); 
    }

    message[buflen] = '\0';
    int altitude = atoi(message);

    delay(10);
    Serial.println(altitude);
  }
}

