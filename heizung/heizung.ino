#include "heizung.h"
#include "display.h"
#include "avr/wdt.h"

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
    // Issue 20 I2C clocks to make sure no slaves are hung in a read
    // no idea if this helps/is useful but found on some forum
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(70, OUTPUT);
    pinMode(71, OUTPUT);
    digitalWrite(20, LOW);
    digitalWrite(70, LOW);
    for (int i = 0; i < 20; i++) {
        digitalWrite(21, LOW);
        digitalWrite(71, LOW);
        delayMicroseconds(10);
        digitalWrite(21, HIGH);
        digitalWrite(71, HIGH);
        delayMicroseconds(10);
    }    
    // Pullups needed for I2C?
    //  https://forum.arduino.cc/index.php?topic=235397.0
    setup_lcd();
 #endif // ENABLE_LCD
}

void loop() {
    wdt_reset(); // serve watchdog
    loop_heizung();
    delay(1000);
}
