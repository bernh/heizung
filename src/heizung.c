#include <stdio.h>

#ifdef TEST
    #include "test.h"
#endif

#include "heizung.h"
#include "ptc.h"

// --- globale Variablen ---
static int t[PTC_NR] = {};
static int outputs[OUTPUT_NR] = {};
//static int heizung_ein_aus = 1;  // digital input

// --- call PTC (or Python test) code ---
void messung(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        t[i] = temperatur_messung(i);
        printf("PTC ID %d: %d°C\n", i, t[i]);
    }
    // TODO heizung_ein_aus = ...
}


int solar_fall_1(int einsprungpunkt) 
{
    // einsprungpunkt irrelevant
    if (t[F2] > (t[F3] + D1)) {
        if (t[F3] < F3max) {
            outputs[UP1] = 1;
        } else {
            return 2;
        }
    } else {
        return 1;
    }
    return 0;
}

int solar_fall_2(int einsprungpunkt) 
{
    if (((einsprungpunkt == 1)  && (t[F1] < (t[F3] + D2))) ||
        (einsprungpunkt == 2)
       ) {

        if ((t[F12] < F12min) &&
            (t[F2] < (t[F7] + D12))
           ) {
            if (t[F2] > (t[F7] + D3)) {
                outputs[ZV5] = 1;
                outputs[UP6] = 1;
            } 
        } else {
            return 1; // überprüfe Fall 3
        }
    }
    return 0;
}

int solar_fall_3(int einsprungpunkt) 
{
    // einsprungpunkt irrelevant
    if (t[F2] > (t[F4] + D4)) {
        if (t[F4] < F4max) {
            outputs[UP2] = 1;
            outputs[UP6] = 1;
        } else {
            return 2; 
        }
    } else {
        return 1;
    }
    return 0;
}

int solar_fall_4(int einsprungpunkt)
{
    if (einsprungpunkt == 1) {
        if (t[F1] < (t[F4] + D5)) {
            if (t[F2] > (t[F5] + D6)) {
                // kein return, bei einsprungpunkt 2 weitermachen
                einsprungpunkt = 2;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }

    if (einsprungpunkt == 2) {
        if (t[F5] < F5max) {
            //TODO outputs[ZV3a] = 1; 
            outputs[UP3] = 1;
            outputs[UP6] = 1;
        } else {
            return 2;
        }
    }
    return 0;
}

int solar_fall_5(int einsprungpunkt) 
{
    if (einsprungpunkt == 1) {
        if ((t[F1] < t[F5] + D7) && (t[F2] > (t[F6] + D8))) {
            // kein return, bei einsprungpunkt 2 weitermachen
        } else {
            return 0;
        }
    }

    if (einsprungpunkt == 2) {
        if (t[F6] < F6max) {
            //TODO outputs[ZV4a] = 1;
            outputs[UP4] = 1;
            outputs[UP6] = 1;
        } else {
            // TODO
            // Alarm, F12 auf -10 Grad setzen
        }
    }
    return 0;
}

void solar(void) 
{
    int retval = 0;

    retval = solar_fall_1(retval);
    if (retval != 0) {
        retval = solar_fall_2(retval);
        if (retval != 0) {
            retval = solar_fall_3(retval);
            if (retval != 0) {
                retval = solar_fall_4(retval);
                if (retval != 0) {
                    retval = solar_fall_5(retval);
                }
            }
        }
    }
}

void kesselfreigabe(void) 
{
    if ((t[F2]  < (t[F7] + D13)) &&
        (t[F10] < (t[F7] + D13)) &&
        (t[F12] < F12min)
       ) {
        outputs[KESSEL] = 1;
    }

    if ((t[F10] > (t[F11] + D9)) &&
        (t[F11] < F11max)
       ) {
        // Fall 7
        outputs[UP8] = 1;
    }
}

void scheitholzkessel(void)
{
    if ((t[F8] > F8min) &&
        (t[F8] > (t[F11] + D9))
       ) {
        // Fall 9
        outputs[UP7] = 1;
    }
}

void ausgaenge(void) 
{
    // initialisiere alle Ausgänge auf 0
    for (int i = 0; i < OUTPUT_NR; i++) {
        outputs[i] = 0;
    }
    solar();
    kesselfreigabe();
    scheitholzkessel();
}

// --- Arduino Funktionen ---

void setup(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        t[i] = -1;
    }
}

void loop(void)
{
    messung();
    ausgaenge();
}

// --- debug ---
int *get_outputs(void)
{
    return &outputs[0];
}
