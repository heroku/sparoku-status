#include "SparkButton.h"

#define STATE_DOWN 0
#define STATE_UP 1
#define STATE_ERROR 2
#define STATE_CRASHED 3
#define STATE_BOOTING 4
#define STATE_IDLE 5

#define RESPONSE_OK 1
#define RESPONSE_SCALE_UP 2
#define RESPONSE_SCALE_DOWN 3
#define RESPONSE_RESTART 4

#define LIGHT_INTENSITY 25 // how bright – 1 to 255

SparkButton strip = SparkButton();

int current[12];
int desired[12];
int drainResponse;
bool blinkingStatus;

void setup() {
    strip.begin();
    strip.allLedsOff();
    for(int i=0; i<12; i++) {
        current[i] = STATE_DOWN;
        desired[i] = STATE_DOWN;
    }
    blinkingStatus = false;
    drainResponse = RESPONSE_OK;
    Spark.function("update", handleUpdate);

    // uncomment below to debug using a terminal with Serial.println(msg);
    // Serial.begin(9600);
}

void loop() {
    if (strip.buttonOn(1)) { // top
        processButton(RESPONSE_SCALE_UP);
    }

    if (strip.buttonOn(2)) { // right
        processButton(RESPONSE_RESTART);
    }

    if (strip.buttonOn(3)) { // down
        processButton(RESPONSE_SCALE_DOWN);
    }

    if (strip.buttonOn(4)) { // left
        processButton(RESPONSE_OK);
    }

    if (drainResponse == RESPONSE_OK) {
        for(int i=0; i<12; i++) {
            updateColor(i);
        }
        blinkingStatus = !blinkingStatus;
        delay(75);
    }
}

void updateColor(int i) {
    // handle solid color
    if (current[i] != desired[i]) {
        switch(desired[i]) {
            case STATE_DOWN:
                strip.ledOff(i);
                break;
            case STATE_UP:
                strip.ledOn(i, 0, LIGHT_INTENSITY, 0);
                break;
            case STATE_ERROR:
                strip.ledOn(i, LIGHT_INTENSITY, 0, 0);
                break;
            case STATE_CRASHED:
                strip.ledOn(i, LIGHT_INTENSITY, 0, 0);
                break;
            case STATE_BOOTING:
                strip.ledOn(i, 0, 0, LIGHT_INTENSITY);
                break;
            case STATE_IDLE:
                strip.ledOn(i, 0, 0, LIGHT_INTENSITY);
                break;
        }
        current[i] = desired[i];
    }
    // blink lights
    else {
        int color = LIGHT_INTENSITY;
        if (blinkingStatus) color -= 15;
        switch(current[i]) {
            case STATE_UP:
                strip.ledOn(i, 0, color, 0);
                break;
            case STATE_ERROR:
                strip.ledOn(i, color, 0, 0);
                break;
            case STATE_BOOTING:
                strip.ledOn(i, 0, 0, color);
                break;
        }
    }
}

void processButton(int response) {
    drainResponse = response;
    strip.allLedsOn(LIGHT_INTENSITY, LIGHT_INTENSITY, LIGHT_INTENSITY);
    for(int i=0; i<12; i++) {
        // flag as dirty so it will go back to whatever color it was
        current[i] = 99;
    }
}

// parses a list of colors separated by semicolons
// COLOR1;COLOR2;...
int handleUpdate(String command) {
    unsigned int i;
    int currentDyno = 1;
    int lastColor;
    String current;

    for(i=0; i<command.length(); i++) {
        String c = String(command.charAt(i));
        if (c == ";") {
            lastColor = atoi(current.c_str());
            desired[currentDyno] = lastColor;
            currentDyno++;
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
