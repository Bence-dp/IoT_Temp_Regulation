#include "model.h"
#include "config.h"


void initStaticInfo(esp_model &esp) {
  esp.latitude = 43.62453842;
  esp.longitude = 7.050628185;
  esp.lowThreshold = LOW_THRESHOLD;
  esp.highThreshold = HIGH_THRESHOLD;
  esp.ident = "ESP32-01";
  esp.user = "GM";
  esp.loc = "A Biot";
  esp.uptime = "55";
  esp.WiFiSSID = "Livebox-B870";
  esp.MAC = "AC:67:B2:37:C9:48";
  esp.IP = "192.168.1.45";
  esp.target_ip = "127.0.0.1";
  esp.target_port = 1880;
  esp.target_sp = 2;
}

