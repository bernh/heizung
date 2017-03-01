#include <stdio.h>
#include "heizung.h"
#include "ptc.h"

// --- globale Variablen ---
static int temperaturen[PTC_NR] = {};
static int outputs[OUTPUT_NR] = {};
static int heizung_ein_aus = 1;  // digital input

// --- call PTC (or Python test) code ---
void messung(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        temperaturen[i] = temperatur_messung(i);
        printf("PTC ID %d: %d°C\n", i, temperaturen[i]);
    }
    // TODO heizung_ein_aus = ...
}

void programm1(void) 
{
    if (temperaturen[F2] > (temperaturen[F3] + D1)) {
        if (temperaturen[F3] < F3max) {
            outputs[UP1] = 1;
        }

    } else {

    }

}

void programm2(void) 
{
    if (temperaturen[F2] < (temperaturen[F7] + D13)) {
        if (temperaturen[F10] < (temperaturen[F7] + D13)) {
            if (temperaturen[F12] < F12min) {
                outputs[BRENNER] = 1;
            }
        }
    }

    if (temperaturen[F10] > (temperaturen[F11] + D9)) {
        if (temperaturen[F11] < F11max) {
            outputs[UP8] = 1;
        }
    }

    if (temperaturen[F8] > F8min) {
        if (temperaturen[F8] > (temperaturen[F11] + D9)) {
            outputs[UP7] = 1;
        }
    }
}

void entscheidung(void) 
{
    for (int i = 0; i < OUTPUT_NR; i++) {
        outputs[i] = 0;
    }
    programm1();
    programm2();
}

// --- Arduino Funktionen ---

void setup(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        temperaturen[i] = -1;
    }
}

void loop(void)
{
    messung();
    entscheidung();
}

// --- debug ---
int *get_outputs(void)
{
    return &outputs[0];
}
