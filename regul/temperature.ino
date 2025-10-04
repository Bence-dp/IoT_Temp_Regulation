#define ONE_WIRE_BUS 23
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

void setupTemp() {
  tempSensor.begin();
  Serial.println("DS18B20 ready");
}

float loopTemp() {
  tempSensor.requestTemperatures();
  float t = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  return t;
}
