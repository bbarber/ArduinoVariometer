#include <VirtualWire.h>
#include "Vario.h"

const int led_pin = 13;
const int transmit_pin = 12;

Vario vario;

void setup()
{
  vario.setup();
  
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

void loop()
{
  float altitude = vario.getRelativeAltitude(); 
  int altitudeRound = round(altitude);
  int msg[] = { altitudeRound };

  char message[4];
  itoa(altitudeRound, message, 10);

  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
 
  delay(50);
}

