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
#define D13    15       // TODO ?

// Temperaturgrenzen
#define F3max  65       // Boilertemperatur unten
#define F4max  65       // Puffertemperatur Sektion 1
#define F5max  65       // Puffertemperatur Sektion 2
#define F6max  90       // Puffertemperatur Sektion 3
#define F8min  65       // minimale Festbrennstoffkesseltemperatur
#define F11max 58       // Boilertemperatur oben

// -----------------------------------------------------------------------------

typedef enum {
    F1,         // Sonenfühler
    F2,         // Kollektofühler
    F3,         // Boilerfühler unten
    F4,         // Pufferfühler Sektion 1
    F5,         // Pufferfühler Sektion 2
    F6,         // Pufferfühler Sektion 3
    F7,         // Heizung Rücklauffühler
    F8,         // Festbrennstoffkesselfühler
    F9,         // Pufferfühler mitte
    F10,        // Pufferfühler oben
    F11,        // Boilerfühler oben
    F12,        // Außentempteraturfühler
} PTC_ID;



void decide(void);
