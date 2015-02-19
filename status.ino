#include "SparkButton.h"

#define OFF 0
#define GREEN 1
#define YELLOW 2
#define RED 3
#define BLUE 4

#define RESPONSE_OK 1
#define RESPONSE_SCALE_UP 2
#define RESPONSE_SCALE_DOWN 3
#define RESPONSE_RESTART 4


SparkButton strip = SparkButton();

int current[12];
int desired[12];
int drainResponse;

void setup() {
    strip.begin();
    strip.allLedsOff();
    for(int i=0; i<12; i++) {
        current[i] = OFF;
        desired[i] = OFF;
    }
    drainResponse = RESPONSE_OK;
    Spark.function("update", handleUpdate);
    Serial.begin(9600);
}

void loop() {
    if (strip.buttonOn(1)) {
        processButton(RESPONSE_SCALE_UP);
    }

    if (strip.buttonOn(2)) {
        processButton(RESPONSE_RESTART);
    }

    if (strip.buttonOn(3)) {
        processButton(RESPONSE_SCALE_DOWN);
    }

    if (drainResponse == RESPONSE_OK) {
        for(int i=0; i<12; i++) {
            if (current[i] != desired[i]) {
                updateColor(i, desired[i]);
                current[i] = desired[i];
            }
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
        case YELLOW:
            strip.ledOn(i, 10, 10, 0);
            break;
        case RED:
            strip.ledOn(i, 10, 0, 0);
            break;
        case BLUE:
            strip.ledOn(i, 0, 0, 10);
            break;
    }
}

void processButton(int response) {
    drainResponse = response;
    strip.allLedsOn(10, 10, 10);
    for(int i=0; i<12; i++) {
        // flag as dirty so it will go back to whatever color it was
        current[i] = 99;
    }
}

// parses a command in the format:
// DYNO1=COLOR1;DYNO2=COLOR2;...
int handleUpdate(String command) {
    Serial.println("Update called: " + command + "\n");

    unsigned int i;
    int lastDyno, lastColor;
    String current;

    for(i=0; i<command.length(); i++) {
        Serial.println("i=" + String(i) + ", curr=" + current);
        String c = String(command.charAt(i));
        if (c == "=") {
            lastDyno = atoi(current.c_str());
            current = "";
        }
        else if (c == ";") {
            lastColor = atoi(current.c_str());
            desired[lastDyno] = lastColor;
            current = "";
        }
        else {
            current += c;
        }
    }
    int response = drainResponse;
    drainResponse = RESPONSE_OK;
    return response;
}
