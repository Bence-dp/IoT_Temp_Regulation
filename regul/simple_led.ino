#include "config.h"

void setupSimpleLEDS() {
  pinMode(SIMPLE_LED_GREEN, OUTPUT);
  pinMode(SIMPLE_LED_RED, OUTPUT);
}

void turnOnLed(int led_pin) {
  digitalWrite(led_pin, HIGH);
}

void turnOffLed(int led_pin) {
  digitalWrite(led_pin, LOW);
}
