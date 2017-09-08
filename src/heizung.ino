#include "heizung.h"

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    setup_heizung();
}

void loop() {
    loop_heizung();
    delay(1000);
}
