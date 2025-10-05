#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>


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

  // --- NET ---
  String uptime;
  String WiFiSSID;
  String MAC;
  String IP;

  // --- REPORTHOST ---
  String target_ip;
  int target_port;
  int target_sp;
};

esp_model esp;

// ==== prototypes ====
void initStaticInfo(esp_model &esp);
void setupSimpleLEDS();
void setupLED();
void setupTemp();
void setupFan();
void setupLum();
void regulation(float temp, int lum);
String serialize(esp_model *em);
int loopLum();
float loopTemp();



//================ SETUP ET LOOP ==========================
void setup() {
  Serial.begin(9600);
  initStaticInfo(esp);
  setupSimpleLEDS();
  setupLED();
  setupTemp();
  setupFan();
  setupLum();
}

void loop() {
  int lumValue = loopLum();
  float tempValue = loopTemp();
  regulation(tempValue, lumValue);
  delay(10000);
}
