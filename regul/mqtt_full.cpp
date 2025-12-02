#include "mqtt_full.h"


/*===== MQTT broker/server ========*/
// in globals.cpp

/*========== Variables ============*/
float temp_max = 0;
String id_max = "";

/*===== ESP is a MQTT Client ======*/
WiFiClient espClient;               // Wifi 
PubSubClient mqttclient(espClient); // MQTT client

/*===== MQTT client setup =====*/
void mqtt_setup() {
  // set server of our MQTT client
  mqttclient.setServer(mqtt_server.c_str(), 1883);
  // set callback when publishes arrive for the subscribed topics
  mqttclient.setCallback(mqtt_pubcallback); 
}

/*============== CALLBACK ===================*/
/* 
 * Callback when a message is published on a subscribed topic.
 */
void mqtt_pubcallback(char* topic, byte* payload, unsigned int length) {

  // Convertir payload -> String
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  USE_SERIAL.print("Topic: ");
  USE_SERIAL.println(topic);
  USE_SERIAL.print("Message JSON: ");
  USE_SERIAL.println(message);

  // Buffer JSON
  StaticJsonDocument<256> doc;

  // Parse
  DeserializationError error = deserializeJson(doc, message);
  if (error) {
    USE_SERIAL.print("Erreur JSON: ");
    USE_SERIAL.println(error.c_str());
    return;
  }



  String id = doc["info"]["ident"];

  if (id != esp.ident ){
    float temperature = doc["status"]["temperature"];
    float latitude    = doc["location"]["gps"]["lat"];
    float longitude   = doc["location"]["gps"]["lon"];
    float distance =   distanceKm(latitude, longitude, esp.latitude, esp.longitude);
    // Affichage
    USE_SERIAL.print("Température = ");
    USE_SERIAL.println(temperature);

    USE_SERIAL.print("Latitude = ");
    USE_SERIAL.println(latitude);

    USE_SERIAL.print("Longitude = ");
    USE_SERIAL.println(longitude);

    USE_SERIAL.print("id = ");
    USE_SERIAL.println(id);

    // Check distance
    if (distance <= 10){
      if (temperature > temp_max){
        temp_max = temperature;
        id_max = id;
      }
    }

  }
  USE_SERIAL.print("Receive Data from ourselves\n");
  

}

void check_hot_spot(){
      if (temp_max < esp.temperature ){
        esp.hotspot = true;
        USE_SERIAL.println("Je suis hotspot");
      } else {
        esp.hotspot = false;
        USE_SERIAL.println("Je ne suis pas hotspot");
      }
}

/*============= SUBSCRIBE to TOPICS ===================*/
void mqtt_subscribe_mytopics() {
  /*
   * Subscribe to MQTT topics :
   * There is no way on checking the subscriptions from a client. 
   * But you can also subscribe WHENEVER you connect. 
   * Then it is guaranteed that all subscriptions are existing.
   * => If the client is already connected then we have already subscribe
   * since connection and subscriptions go together !
   */
  // Checks whether the client is connected to the MQTT server
  while (!mqttclient.connected()) { // Loop until we're reconnected https://pubsubclient.knolleary.net/api
    USE_SERIAL.print("Attempting MQTT connection...");
    
    // Create a client ID from MAC address .. should be unique ascii string and different from all other devices using the broker !
    String mqttclientId = "ESP32-";
    mqttclientId += WiFi.macAddress(); // if we need random : String(random(0xffff), HEX);
    if (mqttclient.connect(
          mqttclientId.c_str(), // Mqttclient Id when connecting to the server : 8-12 alphanumeric character ASCII
			    NULL,   /* No credential */ 
			    NULL
        )){
      USE_SERIAL.println("connected");
	        
      // THEN Subscribe topics
      mqttclient.subscribe(MQTT_TOPIC.c_str());

      //mqttclient.subscribe(TOPIC_LED,1);
      // mqttclient.subscribe(anothertopic ?);
      mqttclient.subscribe(MQTT_TOPIC.c_str());
    } 
    else { // Connection to broker failed : retry !
      USE_SERIAL.print("failed, rc=");
      USE_SERIAL.print(mqttclient.state());
      USE_SERIAL.println(" try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  } // end while
}


void sendMqttReport() {
  // On envoie toutes les infos au broker MQTT
  // esp.piscine_sp
  // on verifie si on doit envoyer un rapport piscine
  static uint32_t tick_piscine = 0;
  if (esp.piscine_sp == 0) return;
  if ( millis() - tick_piscine < esp.piscine_sp * 1000) { 
    return; 
  }
  tick_piscine = millis();

  // Ensure MQTT is connected and process network events
  if (!mqttclient.connected()) {
    // try to (re)connect and subscribe
    mqtt_subscribe_mytopics();
  } else {
    // let the client maintain keepalive and process callbacks
    mqttclient.loop();
  }

  mqttclient.setBufferSize(2048);
  bool published = mqttclient.publish(MQTT_TOPIC.c_str(), serialize(&esp).c_str());
  if (published) {
    Serial.println("Sent to MQTT");
  } else {
    Serial.println("MQTT publish failed");
  }
  bool published2 = mqttclient.publish(MQTT_TOPIC_GR_A.c_str(), serialize(&esp).c_str());
  if (published2) {
    Serial.println("Sent to MQTT GR_A");
  } else {
    Serial.println("MQTT GR_A publish failed");
  }
}

/**
 * Disconnect the MQTT client.
 * Safe to call even if the client is not connected.
 */
void mqtt_disconnect() {
  if (mqttclient.connected()) {
    mqttclient.disconnect();
    USE_SERIAL.println("MQTT client disconnected");
  } else {
    USE_SERIAL.println("MQTT client already disconnected");
  }

}
