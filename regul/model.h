#ifndef MODEL_H
#define MODEL_H

#include <Arduino.h>

// === STRUCTURE POUR LE JSON ===
struct esp_model {
  // --- STATUS ---
  float temperature;
  float luminosity;
  bool regulationState;
  bool fireDetected;
  bool heaterState;
  bool coolerState;
  int fanSpeed;

  // --- LOCATION ---
  const char room[50] = "312";
  const char address[200] = "Les lucioles";
  double latitude;
  double longitude;

  // --- REGULATION ---
  float lowThreshold;
  float highThreshold;

  // --- INFO ---
  String ident;
  String user;
  String loc;
  String name;

  // --- NET ---
  String uptime;
  String WiFiSSID;
  String MAC;
  String IP;

  // --- REPORTHOST ---
  String target_ip;
  int target_port;
  int target_sp;

  // --- PISCINE ---
  bool occuped;
  bool hotspot;
  int piscine_sp; // sampling period for piscine report
};

void initStaticInfo(esp_model &esp);

#endif
