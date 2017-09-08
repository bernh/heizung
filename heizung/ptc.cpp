#include "Arduino.h"

#include "ptc.h"
#include "heizung.h"

//  150.0 / 1024.0 -> degree per analog step
//  or in other words: the resolution of the temperature measurement
static const float k = 0.146484375;  

int temperatur_messung(int ptc_id) {
    //  0 Volts -> -20 degrees Celcius
    //  5 Volts -> 130 degrees Celcius
    float temperature = k * analogRead(analog_pin_mapping[ptc_id]) - 20.0;  
    return int(temperature + 0.5);  // convert to integer
}
