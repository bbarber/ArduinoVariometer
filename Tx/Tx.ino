#include <VirtualWire.h>
#include "Vario.h"

const int led_pin = 2;
const int transmit_pin = 12;
const int rx_pin = 10;

Vario vario;

void setup()
{
  vario.setup();

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
  pinMode(rx_pin, INPUT);
}

void loop()
{
  int rx = pulseIn(rx_pin, HIGH);
  bool isEnabled = rx > 1200;

  if (isEnabled) {
    digitalWrite(led_pin, HIGH);
    float altitude = vario.getRelativeAltitude();
    int altitudeRound = round(altitude);
    int msg[] = { altitudeRound };

    char message[4];
    itoa(altitudeRound, message, 10);

    vw_send((uint8_t *)message, strlen(message));
    vw_wait_tx(); // Wait until the whole message is gone
  }
  else {
    digitalWrite(led_pin, LOW);
  }


  delay(1000);
}

