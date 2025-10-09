#include <ArduinoJson.h>


String serialize(esp_model *em) {
  StaticJsonDocument<1500> doc;

  // === STATUS SECTION ===
  JsonObject status = doc.createNestedObject("status");
  status["temperature"] = em->temperature;
  status["light"] = em->luminosity;
  status["regul"] = em->regulationState ? "RUNNING" : "HALT";
  status["fire"] = em->fireDetected;
  status["heater"] = em->heaterState ? "ON" : "OFF";
  status["cooler"] = em->coolerState ? "ON" : "OFF";
  status["fanspeed"] = em->fanSpeed;

  // === LOCATION SECTION ===
  JsonObject location = doc.createNestedObject("location");
  location["room"] = em->room;
  location["address"] = em->address;
  JsonObject gps = location.createNestedObject("gps");
  gps["lat"] = em->latitude;
  gps["lon"] = em->longitude;

  // === REGULATION SECTION ===
  JsonObject regul = doc.createNestedObject("regul");
  regul["lt"] = em->lowThreshold;
  regul["ht"] = em->highThreshold;

  // === INFO SECTION ===
  JsonObject info = doc.createNestedObject("info");
  info["ident"] = em->ident;
  info["user"] = em->user;
  info["loc"] = em->loc;

  // === NET SECTION ===
  JsonObject net = doc.createNestedObject("net");
  net["uptime"] = em->uptime; 
  net["ssid"] = em->WiFiSSID;
  net["mac"] = em->MAC;
  net["ip"] = em->IP;

  // === REPORTHOST SECTION ===
  JsonObject reporthost = doc.createNestedObject("reporthost");
  reporthost["target_ip"] = em->target_ip;
  reporthost["target_port"] = em->target_port;
  reporthost["sp"] = em->target_sp;

  // === SERIALIZATION ===
  String output;
  serializeJson(doc, output);
  //serializeJsonPretty(doc, output);
  return output;
}
