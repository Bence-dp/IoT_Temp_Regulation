#include "routes.h"

#define USE_SERIAL Serial

/*===================================================*/
String processor(const String & var){
  /* Replaces placeholders in html file with current esp values */
  // Use fields from global `esp` model
  if (var == "TEMPERATURE") return String(esp.temperature);
  if (var == "LIGHT") return String(esp.luminosity);
  if (var == "UPTIME") return esp.uptime;
  if (var == "WHERE") return esp.loc;
  if (var == "SSID") return esp.WiFiSSID;
  if (var == "MAC") return esp.MAC;
  if (var == "IP") return esp.IP;
  if (var == "COOLER") return (esp.coolerState ? "ON" : "OFF");
  if (var == "HEATER") return (esp.heaterState ? "ON" : "OFF");
  if (var == "LT") return String(esp.lowThreshold);
  if (var == "HT") return String(esp.highThreshold);
  if (var == "PRT_IP") return esp.target_ip;
  if (var == "PRT_PORT") return String(esp.target_port);
  if (var == "PRT_T") return String(esp.target_sp);
  return String();
}

/*===================================================*/
void setup_http_routes(AsyncWebServer* server) {
  /* 
   * Sets up AsyncWebServer and routes 
   */
  
  // La fonction serveStatic(); indique au serveur web d'envoyer les fichiers demandés 
  // par le navigateur (comme les images, les feuilles de style, les sources JavaScript, etc.) 
  // et qui sont stockés dans un système de fichiers
  // https://forum.arduino.cc/t/cherche-renseignements-sur-server-servestatic/1182775
  // => premier param la route et second param le repertoire servi (dans le LittleFS) 
  server->serveStatic("/", LittleFS, "/").setTemplateProcessor(processor);  
  
  // Declaring root handler, and action (given as a lambda with "request" parameter) 
  // to be taken when root is requested
  auto root_handler = server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // https://forum.arduino.cc/t/please-explain-syntax-asyncwebserverrequest-request/1020064/2
    //USE_SERIAL.printf("Root route requested !\n"); 
    /* This handler will download index.html (stored as LittleFS file) and will send it back */
    request->send(LittleFS, "/index.html", String(), false, processor); 
    // cf "Respond with content coming from a File containing templates" section in manual !
    // https://github.com/me-no-dev/ESPAsyncWebServer
    // request->send_P(200, "text/html", page_html, processor); // if page_html was a string .   
    });
  
  #ifdef CSS
  // Route to load style.css file
  server.on("/esp.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/esp.css", "text/css");
  });
  #endif
  
  server->on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
      /* Return current temperature value from esp model */
      //USE_SERIAL.printf("GET /temperature request \n");
      request->send(200, "text/plain", String(esp.temperature));
    });

  server->on("/light", HTTP_GET, [](AsyncWebServerRequest *request){
      /* Return current light value from esp model */
      request->send(200, "text/plain", String(esp.luminosity));
    });

  // Provide full JSON status of the device
  server->on("/esp", HTTP_POST, [](AsyncWebServerRequest *request){
      //USE_SERIAL.println("GET /status request");
      // serialize(&esp) is defined in serialization.ino
      request->send(200, "application/json", serialize(&esp));
    });

  // This route allows users to change thresholds values through GET params
  server->on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
      /* A route with a side effect : this get request has a param and should     
       *  set a new light_threshold ... used for regulation !
       */
      // if (request->hasArg("light_threshold")) { // request may have arguments
      //   // set luminosity threshold (use global LUM_LOW)
      //   LUM_LOW = atof(request->arg("light_threshold").c_str());
      //   request->send_P(200, "text/plain", "Threshold Set !");
      // }
      if (request->hasArg("low_threshold")) {
        // set low temperature threshold
        esp.lowThreshold = atof(request->arg("low_threshold").c_str());
        request->send_P(200, "text/plain", "Low Threshold Set !");
        Serial.print("New low temperature threshold: ");
        Serial.println(esp.lowThreshold);
      }
      if (request->hasArg("high_threshold")) {
        // set high temperature threshold
        esp.highThreshold = atof(request->arg("high_threshold").c_str());
        request->send_P(200, "text/plain", "High Threshold Set !");
        Serial.print("New high temperature threshold: ");
        Serial.println(esp.highThreshold);
      }
      if (request->hasArg("fire_threshold")) {
        // set fire temperature threshold
        TEMP_FIRE = atof(request->arg("fire_threshold").c_str());
        request->send_P(200, "text/plain", "Fire Threshold Set !");
        Serial.print("New fire temperarture threshold: ");
        Serial.println(TEMP_FIRE);
      }
    });
  
  server->on("/target", HTTP_POST, [](AsyncWebServerRequest *request){
      /* A route receiving a POST request with Internet coordinates 
       * of the reporting target host.
       */
      Serial.println("Receive Request for a periodic report !"); 
      if (request->hasArg("ip") &&
          request->hasArg("port") &&
          request->hasArg("sp")) {
        // store reporting target in esp model
        esp.target_ip = request->arg("ip");
        esp.target_port = atoi(request->arg("port").c_str());
        esp.target_sp = atoi(request->arg("sp").c_str());
      }
      request->send(LittleFS, "/index.html", String(), false, processor);
    });
  
  // If request doesn't match any route, returns 404.
  server->onNotFound([](AsyncWebServerRequest *request){
      request->send(404);
    });
}
/*===================================================*/

/*
 * Envoi les données au serveur par une requete http post
 */
void sendReportNow(String payload) {
  static uint32_t tick = 0;
  if (esp.target_sp == 0) return;
  if ( millis() - tick < esp.target_sp) { 
    return; 
  }

  WiFiClient client;
  HTTPClient http;

  String serverName = "http://" + esp.target_ip + ":" + String(esp.target_port) + "/esp";
  // Serial.println(serverName);
  http.begin(client, serverName);
  
  // Specify content-type header
  http.addHeader("Content-Type", "text/plain");

  // // Data to send with HTTP POST
  // String httpRequestData = serialize(&esp);
  
  Serial.println("HTTP POST request sent.");
  int httpResponseCode = http.POST(payload);
  
  Serial.print("HTTP Response code : ");
  Serial.println(httpResponseCode);
    
  // Free resources
  http.end();
}
