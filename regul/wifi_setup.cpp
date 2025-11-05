#include "config.h"
#include <WiFi.h>
#include "wifi_utils.h"
bool wifi_setup(){


  /* Connection from a list of SSID */
  wificonnect_multi(HOST_NAME);               
  
  /* WiFi status     --------------------------*/
  if (WiFi.status() == WL_CONNECTED){
    USE_SERIAL.print("\nWiFi connected : yes ! \n"); 
    wifi_printstatus(0);  
    return true;
  } 
  else {
    USE_SERIAL.print("\nWiFi connected : no ! \n"); 
    //  ESP.restart();
    return false;
  }
}