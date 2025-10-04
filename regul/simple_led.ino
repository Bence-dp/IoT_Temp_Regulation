#define SIMPLE_LED1 19
#define SIMPLE_LED2 21

void setupSimpleLEDS() {
  pinMode(SIMPLE_LED1, OUTPUT);
  pinMode(SIMPLE_LED2, OUTPUT);
}

void turnOnLed(int led_pin) {
  digitalWrite(led_pin, HIGH);
}

void turnOffLed(int led_pin) {
  digitalWrite(led_pin, LOW);
}
