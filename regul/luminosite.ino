#define LUX_PIN A5

void setupLum() {
  Serial.println("Light sensor ready");
}

float getLum() {
  int sensorValue = analogRead(LUX_PIN);
  Serial.print("Luminosity: ");
  Serial.println(sensorValue);
  delay(1000);
  return sensorValue;
}
