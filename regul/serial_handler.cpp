#include "serial_handler.h"
#include "globals.h"  // Inclure globals.h pour accéder aux variables
#include <Arduino.h>

void setupSerial() {
  Serial.begin(9600);
}

void updateFromSerial() {
  if (Serial.available() > 0) {
    String serialData = Serial.readStringUntil('\n');
    //Serial.print(serialData + "\n");
    serialData.trim(); // Supprimer les espaces et retours chariot
    
    if (serialData.startsWith("ht=")) {
      HIGH_THRESHOLD = serialData.substring(3).toFloat();
      

    } else if (serialData.startsWith("lt=")) {
      LOW_THRESHOLD = serialData.substring(3).toFloat();
      
/*     
    } else if (serialData.startsWith("temp_fire=")) {
      TEMP_FIRE = serialData.substring(10).toFloat();
     
  
    } else if (serialData.startsWith("lum_low=")) {
      LUM_LOW = serialData.substring(8).toFloat();

    } else if (serialData.startsWith("lum_high=")) {
      LUM_HIGH = serialData.substring(9).toFloat(); */

    }
  }
}