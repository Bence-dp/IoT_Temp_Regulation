#include "model.h"
#include "config.h"
#include "globals.h"

void initStaticInfo(esp_model &esp) {
  esp.name = "P_22201315 P_Claveille P_22200641";
  esp.latitude = 43.55487;
  esp.longitude = 6.93959;
  esp.lowThreshold = LOW_THRESHOLD;
  esp.highThreshold = HIGH_THRESHOLD;
  esp.ident = HOST_NAME;
  esp.user = "GroupeA";
  esp.loc = "A Biot";
  esp.uptime = "55";
  esp.target_ip = "127.0.0.1";
  esp.target_port = 1880;
  esp.target_sp = 2;
  esp.occuped = false;
  esp.hotspot = false;
}
