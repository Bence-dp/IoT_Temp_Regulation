#include "serial_handler.h"
#include "globals.h"
#include <Arduino.h>

String inputBuffer = "";  // Tampon pour accumuler les caractères reçus

void setupSerial() {
  Serial.begin(9600);
}

void updateFromSerial() {
  // Lire tous les caractères disponibles sans bloquer
  while (Serial.available() > 0) {
    char c = Serial.read();

    // Si on atteint une fin de ligne -> traiter la commande
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        processSerialCommand(inputBuffer);
        inputBuffer = "";  // Réinitialiser pour la prochaine commande
      }
    } else {
      inputBuffer += c;  // Ajouter le caractère au buffer
    }
  }
}

void processSerialCommand(String command) {
  command.trim();  // Nettoyer espaces

  if (command.startsWith("ht=")) {
    HIGH_THRESHOLD = command.substring(3).toFloat();
  }
  else if (command.startsWith("lt=")) {
    LOW_THRESHOLD = command.substring(3).toFloat();
  } 
  else if (command.startsWith("temp_fire=")) {
    TEMP_FIRE = command.substring(10).toFloat();
  }
  /*
  else if (command.startsWith("lum_low=")) {
    LUM_LOW = command.substring(8).toFloat();
  }
  else if (command.startsWith("lum_high=")) {
    LUM_HIGH = command.substring(9).toFloat();
  }
  */
}
