#include "led_ring.h"
#include "globals.h"


unsigned long red_block_until = 0;

bool red_active = false;

void set_green() {
    if (millis() < red_block_until) return;
    Serial.println("set_green\n");
    setColorLedRing(GREEN, 5);
    esp.occuped = false;
}

void set_yellow() {
    if (millis() < red_block_until) return;
    Serial.println("set_yellow\n");
    setColorLedRing(strip.Color(255, 255, 0), 5);
    esp.occuped = true;
}

void set_red() {
    Serial.println("set_red\n");
    setColorLedRing(RED, 5);
    red_block_until = millis() + 30000UL;
    red_active = true;
}

void check_occuped(){
    if (millis() > red_block_until) {
        if (red_active) {
            set_green();
            red_active = false;
        } else {
            if (esp.occuped) {
                set_yellow();
            } else {
                set_green();
            }
        }
    }
}

