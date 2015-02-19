#include "SparkButton.h"

SparkButton strip = SparkButton();

void setup() {
    strip.begin();
    strip.allLedsOff();
}

void loop() {
    for(int i=0; i<12; i++) {
        if (rand() % 2 == 0) {
            strip.ledOff(i);
        }
        else {
            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;
            strip.ledOn(i, r, g, b);
        }
    }
    delay(50);
}
