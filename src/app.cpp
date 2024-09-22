#include <Arduino.h>

#include "clock.h"
#include "sensor.h"

#define BAUD_RATE   9600
#define BUFFER_SIZE 64
#define pinDHT11    2


void setup() {
  Serial.begin(BAUD_RATE);
  start_clock();

  Serial.print("*** Begin sampling at: ");
  Serial.println(rtc_get_local_iso());

  start_sensor(pinDHT11);
}

void loop() {
  // DHT11 sampling rate is 1HZ.
  delay(1000);
  Measurement measurement = read_sensor();
  char* parsed_msg = parse_measurement(&measurement);
  Serial.print(parsed_msg);
}





