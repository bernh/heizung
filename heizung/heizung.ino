#include "heizung.h"
#include "display.h"
#include "avr/wdt.h"

void setup() {
    // --- initialize serial connection
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Serial init done");
    // --- configure digital outputs
    for (int i = 0; i < OUTPUT_NR; i++) {
        pinMode(output_pin_mapping[i], OUTPUT);
    }
    // --- initialize LCD
    setup_lcd();
    // --- initialize temperatures and outputs
    setup_heizung();
    // --- activate watchdog with 2s
    wdt_enable(WDTO_2S);
}

void loop() {
    wdt_reset(); // serve watchdog
    loop_heizung();
    delay(1000);
}
