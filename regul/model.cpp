#include "model.h"
#include "config.h"
#include "globals.h"

void initStaticInfo(esp_model &esp) {
  esp.latitude = 43.57;
  esp.longitude = 7.06;
  esp.lowThreshold = LOW_THRESHOLD;
  esp.highThreshold = HIGH_THRESHOLD;
  esp.ident = HOST_NAME;
  esp.user = "Daniel";
  esp.loc = "Vallauris";
  esp.uptime = "55";
  esp.target_ip = "127.0.0.1";
  esp.target_port = 1880;
  esp.target_sp = 2;
  esp.occuped = false;
  esp.hotspot = false;
}
