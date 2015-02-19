#include "SparkButton.h"

#define OFF 0
#define GREEN 1
#define YELLOW 2
#define RED 3

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
    Serial.begin(9600);
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
        case YELLOW:
            strip.ledOn(i, 10, 10, 0);
            break;
        case RED:
            strip.ledOn(i, 10, 0, 0);
            break;
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
    return 1;
}
