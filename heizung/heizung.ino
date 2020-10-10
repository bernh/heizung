#include "heizung.h"
#include "display.h"
#include "avr/wdt.h"
#include <Wire.h>

void setup() {
    // --- initialize temperatures and outputs
    setup_heizung();

    // --- configure digital outputs
    for (int i = 0; i < OUTPUT_NR; i++) {
        pinMode(output_pin_mapping[i], OUTPUT);
    }

    // --- activate watchdog with 4s
    wdt_enable(WDTO_4S);
    
#ifdef ENABLE_SERIAL
    // --- initialize serial connection
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Serial init done");
#endif // ENABLE_SERIAL
    
#ifdef ENABLE_LCD
    // --- initialize LCD    
    setup_lcd();

    // set timeout to avoid I2C problems, new in Arduino 1.8.3 (update via Boards Manager!)
    // https://github.com/arduino/ArduinoCore-avr/pull/107
    Wire.setWireTimeout(25000, true);
#endif // ENABLE_LCD

}

void loop() {
    wdt_reset(); // serve watchdog
    loop_heizung();
    delay(1000);
}
