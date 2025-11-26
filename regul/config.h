#ifndef CONFIG_H
#define CONFIG_H

// Serial 
#define USE_SERIAL Serial

// Pin pour la led de feu
#define FIRE_LED_PIN 2  

// Pin de la petite LED verte
#define SIMPLE_LED_GREEN 19

// Pin de la petite LED rouge
#define SIMPLE_LED_RED 21

// Pin de la bande de LEDs
#define LED_PIN 13

// Pin du ventilateur
#define FANPIN 27 

// Pin du capteur de lumière
#define LUX_PIN A5

// Pin du capteur de température
#define ONE_WIRE_BUS 23

// Pin de la led pour le feu
#define FIRE_LED_PIN 2

// Taille de l'historique des valeurs de temp et lum
#define HISTORY_SIZE 5

// Hostname de l'ESP
#define HOST_NAME "Daniel"

#endif
