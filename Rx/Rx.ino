
#include <VirtualWire.h>
#include <Wire.h>

const int led_pin = 13;
const int receive_pin = 11;

void setup() {
  Serial.begin(9600);
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);  // Bits per sec
  vw_rx_start();
  Wire.begin();
  pinMode(led_pin, OUTPUT);
}


void loop() {
  int altitude = getAltitude();

  if(altitude != -1) {
    transmitAltitude(altitude);
  }
  
  delay(500);
}

void transmitAltitude(int altitude) {
  digitalWrite(led_pin, HIGH);
  Wire.beginTransmission(8);
  char message[4];
  itoa(altitude, message, 10);
  Wire.write(message);
  Wire.endTransmission();
  digitalWrite(led_pin, LOW);
}

int getAltitude()
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

    return altitude;
  }

  // We didn't recieve anything
  // from the rf transmitter 
  return -1;
}


