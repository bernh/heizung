#include "Arduino.h"

#include "heizung.h"

void set_outputs(int *outputs) {
    for (int i = 0; i < OUTPUT_NR; i++) {
        if (outputs[i] == 1) {
            digitalWrite(output_pin_mapping[i], LOW);
        } else {
            digitalWrite(output_pin_mapping[i], HIGH);
        }
    }
}
