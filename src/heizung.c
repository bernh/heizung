#include <stdio.h>
#include "heizung.h"

// --- globale Variablen ---
static int temperaturen[PTC_NR] = {};




void decide(void)
{
    printf("decide...\n");
}


void messung(void)
{
    for (int i = 0; i++; i < PTC_NR) {
        temperaturen[i] = temperatur_messung(i);
    }
}
