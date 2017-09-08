#include "heizung.h"

void setup() {
    Serial.begin(9600);
    // configure digital outputs
    for (int i = 0; i < OUTPUT_NR; i++) {
        pinMode(output_pin_mapping[i], OUTPUT);
    }
    setup_heizung();
}

void loop() {
    loop_heizung();
    delay(1000);
}
