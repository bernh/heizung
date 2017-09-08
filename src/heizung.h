void setup_heizung(void);
void loop_heizung(void);

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
#define F2      1       // Kollektofühler
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
#define ZV3a    3       // Zonenventil 3a - Umschaltung Sektion 1 auf 2
#define UP4     4       // Umwälzpumpe 4 - Pufferladung Sektion 3
#define ZV4a    5       // Zonenventil 4a - Umschaltung Sektion 2 auf 3
#define ZV5     6       // Zonenventil 5 - Umschaltg. Solardirektheizung
#define UP6     7       // Umwälzpumpe 6 - Solarspeisung PWT
#define UP7     8       // Umwälzpumpe 7 - Pufferladung Holzkessel
#define UP8     9       // Umwälzpumpe 8 - Boilerladung Puffer
#define UP9     10      // Umwälzpumpe 9 - Heizungsumlaufpumpe
#define UP10    11      // Umwälzpumpe 10 - Boilerladung Pelletskessel
#define KESSEL  12      // Pelletskessel - Brennerfreigabe

#define OUTPUT_NR 13

