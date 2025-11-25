#ifndef ROUTES_H
#define ROUTES_H

#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include "routes.h"
#include "FS.h"
#include <LittleFS.h>
#include "globals.h"
#include <HTTPClient.h>
#include "serialization.h"

// forward declaration to avoid including ESPAsyncWebServer.h here
class AsyncWebServer;

void setup_http_routes(AsyncWebServer* server);
String processor(const String& var);
void sendReportNow(String payload);

#endif
