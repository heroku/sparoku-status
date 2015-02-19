#include "SparkButton.h"

#define OFF 0
#define GREEN 1
#define RED 2


SparkButton strip = SparkButton();

int current[12];
int desired[12];

void setup() {
    strip.begin();
    strip.allLedsOff();
    for(int i=0; i<12; i++) {
        current[i] = OFF;
        desired[i] = OFF;
    }
    Spark.function("update", handleUpdate);
}

void loop() {
    for(int i=0; i<12; i++) {
        if (current[i] != desired[i]) {
            updateColor(i, desired[i]);
            current[i] = desired[i];
        }
    }
}

void updateColor(int i, int state) {
    switch(state) {
        case OFF:
            strip.ledOff(i);
            break;
        case GREEN:
            strip.ledOn(i, 0, 10, 0);
            break;
        case RED:
            strip.ledOn(i, 10, 0, 0);
            break;
    }
}

int handleUpdate(String command) {
    int n = atoi(command.c_str());
    desired[n] = GREEN;
    desired[n+1] = RED;
    return 1;
}