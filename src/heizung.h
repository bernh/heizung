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
#define F12min 10       // TODO? 

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

// -----------------------------------------------------------------------------

#define UP1     0       // Umwälzpumpe 1 - Boilerladung Solar
#define UP2     1       // Umwälzpumpe 2 - Pufferladung Sektion 1
#define UP3     2       // Umwälzpumpe 3 - Pufferladung Sektion 2
#define UP4     3       // Umwälzpumpe 4 - Pufferladung Sektion 3
#define ZV5     4       // Zonenventil 5 - Umschaltg. PLT/Puffer
#define UP6     5       // Umwälzpumpe 6 - Solarspeisung PLT
#define UP7     6       // Umwälzpumpe 7 - Boilerladung Holzkessel
#define UP8     7       // Umwälzpumpe 8 - Boilerladung Puffer
#define BRENNER 8       // Ölbrenner     - Brennerfreigabe
#define UP10    9       // Umwälzpumpe 10 - Boilerladung Ölkessel
#define ZV10   10       // Zonenventil 10 - Umschaltg. Öl/Solar


#define OUTPUT_NR 11
