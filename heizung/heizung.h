#ifdef PC_TEST
    #include "test.h"
#else
    #include "Arduino.h"
#endif


void setup_heizung(void);
void loop_heizung(void);
void loop_output_test(void);

// --- Konfiguration ----------------------------------------------------------

// Temperaturdifferenzen
#define D1      7       // Kollektorfühler und Boiler unten
#define D2      7       // Sonnenfühler und Boiler unten
#define D3     15       // Kollektorfühler und Heizung Rücklauf 
#define D4      7       // Kollektorfühler und Pufferfühler Sektion 1 (oben)
#define D5      7       // Sonnenfühler und Pufferfühler Sektion 1 (oben)
#define D6      7       // Kollektorfühler und Pufferfühler Sektion 2 (mitte)
#define D7      7       // Sonnenfühler und Pufferfühler Sektion 2 (mitte)
#define D8      7       // Kollektorfühler und Pufferfühler Sektion 3 (unten)
#define D9     10       // Pufferfühler oben und Boiler oben
#define D10    15       // Pufferfühler oben und Rücklauffühler
#define D11     5       // Pufferfühler mitte und Festbrennstoffkesselfühler
#define D12    30       // Kollektorfühler und Heizung Rücklauf
#define D13    15       // Kollektorfühler und Heizung Rücklauf 

// Temperaturgrenzen
#define F3max  65       // Boilertemperatur unten
#define F4max  65       // Puffertemperatur Sektion 1
#define F5max  65       // Puffertemperatur Sektion 2
#define F6max  90       // Puffertemperatur Sektion 3
#define F8min  65       // minimale Festbrennstoffkesseltemperatur
#define F11max 58       // Boilertemperatur oben
#define F12min 10       // Außentemperatur

// -----------------------------------------------------------------------------

#define F1      0       // Sonnenfühler
#define F2      1       // Kollektorfühler
#define F3      2       // Boilerfühler unten
#define F4      3       // Pufferfühler Sektion 1
#define F5      4       // Pufferfühler Sektion 2
#define F6      5       // Pufferfühler Sektion 3
#define F7      6       // Heizung Rücklauffühler
#define F8      7       // Festbrennstoffkesselfühler
#define F9      8       // Pufferfühler mitte
#define F10     9       // Pufferfühler oben
#define F11    10       // Boilerfühler oben
#define F12    11       // Außentempteraturfühler

#define PTC_NR 12

static const int analog_pin_mapping[PTC_NR]  = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};

// -----------------------------------------------------------------------------

#define UP1     0       // Umwälzpumpe 1 - Boilerladung Solar
#define UP2     1       // Umwälzpumpe 2 - Pufferladung Sektion 1
#define UP3     2       // Umwälzpumpe 3 - Pufferladung Sektion 2
#define UP4     3       // Umwälzpumpe 4 - Pufferladung Sektion 3
#define ZV5     4       // Zonenventil 5 - Zonenventil Solardirektheizung
#define UP6     5       // Umwälzpumpe 6 - Solarspeisung PWT
#define UP7     6       // Umwälzpumpe 7 - Pufferladung Holzkessel
#define UP8     7       // Umwälzpumpe 8 - Boilerladung Puffer
#define KESSEL  8       // Pelletskessel - Brennerfreigabe
#define ZV3a    9       // Zonenventil3a - Zonenventil 3a Sektion 1 auf 2
#define ZV4a    10      // Zonenventil4a - Zonenventil 4a Sektion 2 auf 3
#define ALARM   11


#define OUTPUT_NR 12

static const int output_pin_mapping[OUTPUT_NR] = {22, 25, 26, 29, 30, 33, 34, 37, 38, 41, 42, 45};

