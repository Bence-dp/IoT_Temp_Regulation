/*********
	Based on Rui Santos work : https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
	File mqtt_full/mqtt_full.ino
	Modified by GM

	Tests with CLI :
	
  mosquitto_pub  -h test.mosquitto.org -t "uca/M1/iot/led" -m "{\"led\" : \"ON\"}" -q 1
  mosquitto_sub  -h test.mosquitto.org -t "uca/M1/iot/temp"  -q 1
*********/

#include "mqtt_full.h"


// TODO: garder 2 variables gloables
// - max_temp
// - id de celui-ci, pour update max_temp si jamais sa temp descend

double EARTH_RADIUS_KM = 6371.0;


double deg2rad(double deg) {
    return deg * 3.14159265358979323846 / 180.0;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    double a = sin(dLat/2) * sin(dLat/2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               sin(dLon/2) * sin(dLon/2);

    return 2 * EARTH_RADIUS_KM * asin(sqrt(a));
}




/*===== MQTT broker/server ========*/
//const char* mqtt_server = "192.168.1.101"; 
//const char* mqtt_server = "public.cloud.shiftr.io"; // Failed in 2021
// need login and passwd (public,public) mqtt://public:public@public.cloud.shiftr.io
// const char* mqtt_server = "broker.hivemq.com"; // anynomous Ok in 2021 
const char* mqtt_server = "10.0.1.58"; 

// const char* mqtt_server = "192.168.19.211"; // anynomous Ok in 2021
//const char* mqtt_server = "mqtt.eclipseprojects.io"; // anynomous Ok in 2021

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
  USE_SERIAL.print("Message arrived on topic : ");
  USE_SERIAL.println(topic);
  USE_SERIAL.print("=> ");

  // Byte list (of the payload) to String and print to Serial
  String message;
  for (int i = 0; i < length; i++) {
    //USE_SERIAL.print((char)payload[i]);
    message += (char)payload[i];
  }
  USE_SERIAL.println(message);

  // Parse JSON
  StaticJsonDocument<768> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    USE_SERIAL.print("JSON error: ");
    USE_SERIAL.println(error.c_str());
    return;
  }

  // Extract remote ESP temperature
  float remote_temp = doc["status"]["temperature"];

  // Extract remote GPS position
  double remote_lat = doc["location"]["gps"]["lat"];
  double remote_lon = doc["location"]["gps"]["lon"];

  USE_SERIAL.printf("Remote temp = %.2f°C\n", remote_temp);
  USE_SERIAL.printf("Remote GPS = (%.5f, %.5f)\n", remote_lat, remote_lon);

  // Compute distance using Haversine formula
  double dist_km = haversineDistance(esp.latitude, esp.longitude, remote_lat, remote_lon);

  USE_SERIAL.printf("Distance = %.3f km\n", dist_km);

  // Check distance
  if (dist_km <= 10.0) {
    USE_SERIAL.println("ESP is within 10km radius");

    // Compare temperatures
    if (remote_temp > getTemp()) {
      USE_SERIAL.println("Remote temperature is HIGHER.");
      esp.hotspot = false;
      USE_SERIAL.println("Set hotspot to false.");
    } else if (remote_temp < getTemp()) {
      USE_SERIAL.println("Remote temperature is LOWER.");
      esp.hotspot = true;
      USE_SERIAL.println("Set hotspot to true.");
    } else {
      USE_SERIAL.println("Temperatures are equal.");
      esp.hotspot = false;
      USE_SERIAL.println("Set hotspot to false.");
    }
  }
  else {
    USE_SERIAL.println("ESP is farther than 10km ");
  }

  /*
  char msg[length + 1];
  memcpy(msg, payload, length);
  msg[length] = NULL;
  message = String(msg);
  */

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic, you check if the message is either "on" or "off".
  // Here we change the output state according to the message ... why not !
/*   if (String(topic) == TOPIC_LED) {
    USE_SERIAL.print("so ... changing output to ");
    if (message == "on") {
      USE_SERIAL.println("on");
      set_LED(HIGH);
    }
    else if (message == "off") {
      USE_SERIAL.println("off");
      set_LED(LOW);
    }
  } */
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
      //mqttclient.subscribe(TOPIC_LED,1);
      // mqttclient.subscribe(anothertopic ?);
      mqttclient.subscribe(MQTT_TOPIC);
    } 
    else { // Connection to broker failed : retry !
      USE_SERIAL.print("failed, rc=");
      USE_SERIAL.print(mqttclient.state());
      USE_SERIAL.println(" try again in 5 seconds");
      delay(5000); // Wait 5 seconds before retrying
    }
  } // end while
}
