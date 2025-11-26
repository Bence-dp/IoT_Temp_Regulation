/*********
	Based on Rui Santos work : https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
	File mqtt_full/mqtt_full.ino
	Modified by GM

	Tests with CLI :
	
  mosquitto_pub  -h test.mosquitto.org -t "uca/M1/iot/led" -m "{\"led\" : \"ON\"}" -q 1
  mosquitto_sub  -h test.mosquitto.org -t "uca/M1/iot/temp"  -q 1
*********/

#include "mqtt_full.h"


/*===== MQTT broker/server ========*/
//const char* mqtt_server = "192.168.1.101"; 
//const char* mqtt_server = "public.cloud.shiftr.io"; // Failed in 2021
// need login and passwd (public,public) mqtt://public:public@public.cloud.shiftr.io
//const char* mqtt_server = "broker.hivemq.com"; // anynomous Ok in 2021 
//const char* mqtt_server = "192.168.19.211"; // anynomous Ok in 2021
const char* mqtt_server = "10.0.1.58";
//const char* mqtt_server = "mqtt.eclipseprojects.io"; // anynomous Ok in 2021
float temp_max = 0;
String id_max = "";
/*===== ESP is a MQTT Client =======*/
WiFiClient espClient;               // Wifi 
PubSubClient mqttclient(espClient); // MQTT client

/*===== MQTT client setup =====*/
void mqtt_setup() {
  // set server of our MQTT client
  mqttclient.setServer(mqtt_server, 1883);
  // set callback when publishes arrive for the subscribed topics
  mqttclient.setCallback(mqtt_pubcallback); 
}

/*============== CALLBACK ===================*/
/* 
 * Callback when a message is published on a subscribed topic.
 */

void mqtt_pubcallback(char* topic, byte* payload, unsigned int length) {

  // Convertir payload → String
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message JSON: ");
  //Serial.println(message);

  // Buffer JSON
  StaticJsonDocument<256> doc;

  // Parse
  DeserializationError error = deserializeJson(doc, message);
  if (error) {
    Serial.print("Erreur JSON: ");
    Serial.println(error.c_str());
    return;
  }


  // Récupérer les valeurs
  float temperature = doc["status"]["temperature"];
  float latitude    = doc["location"]["gps"]["lat"];
  float longitude   = doc["location"]["gps"]["lon"];
  String id = doc["info"]["ident"];
  float distance =   distanceKm(latitude, longitude, esp.latitude, esp.longitude);
    // Affichage
  Serial.print("Température = ");
  Serial.println(temperature);

  Serial.print("Latitude = ");
  Serial.println(latitude);

  Serial.print("Longitude = ");
  Serial.println(longitude);

  Serial.print("id = ");
  Serial.println(id);

  if (distance <= 10){
    if (temperature > temp_max){
      temp_max = temperature;
      id_max = id;
    }
    if (temp_max < esp.temperature ){
      
      esp.hotspot = true;
      Serial.print("Je suis hotspot");
      
    }
    else{
      esp.hotspot = false;
      Serial.print("Je ne suis pas hotspot");



    }
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
      mqttclient.subscribe("uca/iot/master");

      //mqttclient.subscribe(TOPIC_LED,1);
      // mqttclient.subscribe(anothertopic ?);
    } 
    else { // Connection to broker failed : retry !
      USE_SERIAL.print("failed, rc=");
      USE_SERIAL.print(mqttclient.state());
      USE_SERIAL.println(" try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  } // end while
}


