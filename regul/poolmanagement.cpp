#include "led_ring.h"
#include "globals.h"


unsigned long red_block_until = 0;
String last_color;
void set_green() {
    if (millis() < red_block_until) return;
    Serial.println("set_green\n");
    setColorLedRing(GREEN, 5);
    esp.occuped = false;
    last_color = "green";
}

void set_yellow() {
    
    if (millis() < red_block_until) return;
    Serial.println("set_yellow\n");
    setColorLedRing(strip.Color(255, 255, 0), 5);
    esp.occuped = true;
    last_color = "yellow";
}

void set_red() {
     Serial.println("set_red\n");
    setColorLedRing(RED, 5);
    red_block_until = millis() + 30000UL;
}

void check_occuped(){
    if (millis() < red_block_until) return;
    if (esp.luminosity > 3000){
        set_green();
    }
}

