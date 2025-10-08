#include "config.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

void setupTemp() {
  tempSensor.begin();
  Serial.println("DS18B20 ready");
}

float getTemp() {
  tempSensor.requestTemperatures();
  float t = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  return t;
}
