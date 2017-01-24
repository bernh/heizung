#include <stdio.h>
#include "heizung.h"
#include "ptc.h"

// --- globale Variablen ---
static int temperaturen[PTC_NR] = {};


void messung(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        temperaturen[i] = temperatur_messung(i);
        printf("PTC ID %d: %d°C\n", i, temperaturen[i]);
    }
}

// --- Arduino Funktionen ---

void setup(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        temperaturen[i] = -1;

    }
    printf("setup called\n");
}

void loop(void)
{
    messung();
    printf("loop called\n");

}

