#ifdef PC_TEST
    #include <stdio.h>
#else
    #include "Arduino.h"
    #include "utils.h"
#endif

#include "heizung.h"
#include "ptc.h"
#include "outputs.h"
#include "compare.h"
#include "display.h"

// --- globale Variablen ---
static int t[PTC_NR] = {};
static int outputs[OUTPUT_NR] = {};


// --- call PTC (or Python test) code ---
void messung(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        t[i] = temperatur_messung(i);
    }
}


int solar_boilerladung(int einsprungpunkt) 
{
    // einsprungpunkt irrelevant
    if (F2_bigger_F3_plus_D1(t)) {
        if (F3_smaller_F3max(t)) {
            outputs[UP1] = 1;
        } else {
            return 2;
        }
    } else {
        return 1;
    }
    return 0;
}

int solar_direktheizung(int einsprungpunkt) 
{
    if (((einsprungpunkt == 1)  && F1_smaller_F3_plus_D2(t)) ||
        (einsprungpunkt == 2)
       ) {

        if (F12_smaller_F12min(t) &&
            F2_smaller_F7_plus_D12(t)
           ) {
            if (F2_bigger_F7_plus_D3(t)) {
                outputs[ZV5] = 1;
                outputs[UP6] = 1;
            } 
        } else {
            return 1; // überprüfe Fall 3
        }
    }
    return 0;
}

int solar_pufferladung_sekt_1(int einsprungpunkt) 
{
    // einsprungpunkt irrelevant
    if (F2_bigger_F4_plus_D4(t)) {
        if (F4_smaller_F4max(t)) {
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

int solar_pufferladung_sekt_2(int einsprungpunkt)
{
    if (einsprungpunkt == 1) {
        if (F1_smaller_F4_plus_D5(t)) {
            if (F2_bigger_F5_plus_D6(t)) {
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
        if (F5_smaller_F5max(t)) {
            outputs[ZV3a] = 1; 
            outputs[UP3] = 1;
            outputs[UP6] = 1;
        } else {
            return 2;
        }
    }
    return 0;
}

int solar_pufferladung_sekt_3(int einsprungpunkt) 
{
    // return 1 für ALARM, sonst immer 0
    if (einsprungpunkt == 1) {
        if (F1_smaller_F5_plus_D7(t) && F2_bigger_F6_plus_D8(t)) {
            // kein return, bei einsprungpunkt 2 weitermachen
            einsprungpunkt = 2;
        } else {
            return 0;
        }
    }

    if (einsprungpunkt == 2) {
        if (F6_smaller_F6max(t)) {
            outputs[ZV4a] = 1;
            outputs[UP4] = 1;
            outputs[UP6] = 1;
        } else {
            return 1; // ALARM
        }
    }
    return 0;
}

void solar(void) 
{
    int retval = 0;

    retval = solar_boilerladung(retval);
    if (retval != 0) {
        retval = solar_direktheizung(retval);
        if (retval != 0) {
            retval = solar_pufferladung_sekt_1(retval);
            if (retval != 0) {
                retval = solar_pufferladung_sekt_2(retval);
                if (retval != 0) {
                    retval = solar_pufferladung_sekt_3(retval);
                    if (retval != 0) {
                        outputs[ALARM] = 1;
                        outputs[UP7] = 1;
                    }
                }
            }
        }
    }
}

void kesselfreigabe(void) 
{
    if (F2_smaller_F7_plus_D13(t) &&
        F10_smaller_F7_plus_D13(t) &&
        F12_smaller_F12min(t)
       ) {
        outputs[KESSEL] = 1;
    }

    if (F10_bigger_F11_plus_D9(t) &&
        F11_smaller_F11max(t)
       ) {
        // Fall 7
        outputs[UP8] = 1;
    }
}

void scheitholzkessel(void)
{
    if (F8_bigger_F8min(t) &&
        F8_bigger_F11_plus_D9(t)
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
    set_outputs(outputs);
}

// --- Arduino Funktionen ---

void setup_heizung(void)
{
    for (int i = 0; i < PTC_NR; i++) {
        t[i] = -1;
    }
    for (int i = 0; i < OUTPUT_NR; i++) {
        outputs[i] = 0;
    }
    set_outputs(outputs);
}

void loop_heizung(void)
{
    messung();
    #ifndef PC_TEST
    display(t);
    #endif
    ausgaenge();
}

// --- debug ---
void loop_output_test(void)
{
    outputs[UP1   ] = 1;
    outputs[UP2   ] = 1;
    outputs[UP3   ] = 1;
    outputs[UP4   ] = 1;
    outputs[ZV5   ] = 1;
    outputs[UP6   ] = 1;
    outputs[UP7   ] = 1;
    outputs[UP8   ] = 1;
    outputs[KESSEL] = 1;
    outputs[ZV3a  ] = 1;
    outputs[ZV4a  ] = 1;
    outputs[ALARM ] = 1;
    set_outputs(outputs);
}


int *get_outputs(void)
{
    return &outputs[0];
}
