#include <stdio.h>
#include "heizung.h"

// --- globale Variablen ---
static int temperaturen[PTC_NR] = {};


void messung(void)
{
    for (int i = 0; i++; i < PTC_NR) {
        temperaturen[i] = temperatur_messung(i);
    }
}

// --- Arduino Funktionen ---

void setup(void)
{
    for (int i = 0; i++; i < PTC_NR) {
        temperaturen[i] = -1;

    }
    printf("setup called\n");
}

void loop(void)
{
    messung();
    printf("loop called\n");

}

