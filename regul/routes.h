
#ifndef ROUTES_H
#define ROUTES_H

#include <Arduino.h>
// forward declaration to avoid including ESPAsyncWebServer.h here
class AsyncWebServer;

void setup_http_routes(AsyncWebServer* server);
String processor(const String& var);

#endif // ROUTES_H