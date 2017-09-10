#include <iostream>
using namespace std;

#include "gtest/gtest.h"

#include "heizung.h"
#include "compare.h"

// global variables (-> our test cases are not thread safe!)
static int outputs[OUTPUT_NR] = {1,2,3,4,5,6,7,8,9,10,11,12};
static int t[PTC_NR] = {};

// --- interface functions to Arduino code ---------------------

// copy output values into global variable
void set_outputs(int *outs) {
    for (int i = 0; i < OUTPUT_NR; i++) {
        outputs[i] = outs[i];
    }
}

// get values from global variable
int temperatur_messung(int ptc_id) {
    return t[ptc_id];
}

// --- Tests --------------------------------------------------

TEST(Basic, Compare_Smaller) {
    int t1, t2, state;
    t1 = 10;
    t2 = 20;
    state = 0;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is TRUE

    t1 = 20;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is TRUE

    t1 = 21;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is still TRUE

    t1 = 22;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 0); // t1 < t2 is FALSE now

    t1 = 21;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 0); // t1 < t2 is FALSE

    t1 = 20;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 0); // t1 < t2 is FALSE

    t1 = 19;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 0); // t1 < t2 is still FALSE

    t1 = 18;
    t2 = 20;
    state = compare(t1, t2, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is TRUE again
}


TEST(Basic, Compare_Bigger) {
    int t1, t2, state;
    t1 = 10;
    t2 = 20;
    state = 0;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 0); // t1 > t2 is FALSE

    t1 = 20;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 0); // t1 > t2 is FALSE

    t1 = 21;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 0); // t1 > t2 is still FALSE

    t1 = 22;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 1); // t1 > t2 is TRUE now

    t1 = 21;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is TRUE

    t1 = 20;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 1); // t1 > t2 is TRUE

    t1 = 19;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 1); // t1 < t2 is still TRUE

    t1 = 18;
    t2 = 20;
    state = compare(t2, t1, 1, state);
    ASSERT_EQ(state, 0); // t1 > t2 is FALSE again
}


class HeizungsTest : public testing::Test {

    protected:  
        virtual void SetUp() {
            setup_heizung();
        }

        virtual void TearDown() {
            // do nothing
        }

        void print_state(void) {
            cout << setw(34) << left << "Sonnenfühler"               << "F1  " << t[0] << "°C" << endl;
            cout << setw(34) << left << "Kollektorfühler"            << "F2  " << t[1] << "°C" << endl;
            cout << setw(34) << left << "Boilerfühler unten"         << "F3  " << t[2] << "°C" << endl;
            cout << setw(34) << left << "Pufferfühler Sektion 1"     << "F4  " << t[3] << "°C" << endl;
            cout << setw(34) << left << "Pufferfühler Sektion 2"     << "F5  " << t[4] << "°C" << endl;
            cout << setw(34) << left << "Pufferfühler Sektion 3"     << "F6  " << t[5] << "°C" << endl;
            cout << setw(34) << left << "Heizung Rücklauffühler"     << "F7  " << t[6] << "°C" << endl;
            cout << setw(34) << left << "Festbrennstoffkesselfühler" << "F8  " << t[7] << "°C" << endl;
            cout << setw(34) << left << "Pufferfühler mitte"         << "F9  " << t[8] << "°C" << endl;
            cout << setw(34) << left << "Pufferfühler oben"          << "F10 " << t[9] << "°C" << endl;
            cout << setw(34) << left << "Boilerfühler oben"          << "F11 " << t[10] << "°C" << endl;
            cout << setw(34) << left << "Außentempteraturfühler"     << "F12 " << t[11] << "°C" << endl;
            cout << "----------------------------------------------------" << endl;
            cout << setw(34) << left << "Boilerladung Solar"             << "UP1    " << outputs[0] << endl;
            cout << setw(34) << left << "Pufferladung Sektion 1"         << "UP2    " << outputs[1] << endl;
            cout << setw(34) << left << "Pufferladung Sektion 2"         << "UP3    " << outputs[2] << endl;
            cout << setw(34) << left << "Pufferladung Sektion 3"         << "UP4    " << outputs[3] << endl;
            cout << setw(34) << left << "Zonenventil Solardirektheizung" << "ZV5    " << outputs[4] << endl;
            cout << setw(34) << left << "Solarspeisung PWT"              << "UP6    " << outputs[5] << endl;
            cout << setw(34) << left << "Pufferladung Holzkessel"        << "UP7    " << outputs[6] << endl;
            cout << setw(34) << left << "Boilerladung Puffer"            << "UP8    " << outputs[7] << endl;
            cout << setw(34) << left << "Brennerfreigabe"                << "KESSEL " << outputs[8] << endl;
            cout << setw(34) << left << "Zonenventil 3a Sektion 1 auf 2" << "ZV3a   " << outputs[9] << endl;
            cout << setw(34) << left << "Zonenventil 4a Sektion 2 auf 3" << "ZV4a   " << outputs[10] << endl;
            cout << setw(34) << left << "ALARM"                          << "ALARM  " << outputs[11] << endl;
        }
};

TEST_F(HeizungsTest, Boilerladung) {

    int _F3 = 50;
    int temperatures[PTC_NR] = {
        100, // Sonnenfühler
        _F3 + D1 + 10, // Kollektorfühler
        _F3, // Boilerfühler unten
        20, // Pufferfühler Sektion 1
        30, // Pufferfühler Sektion 2
        40, // Pufferfühler Sektion 3
        40, // Heizung Rücklauffühler
        20, // Festbrennstoffkesselfühler
        30, // Pufferfühler mitte
        45, // Pufferfühler oben
        60, // Boilerfühler oben
        0   // Außentempteraturfühler
    };
    memcpy(t, temperatures, sizeof(temperatures));
    loop_heizung();
    print_state();
    ASSERT_EQ(outputs[UP1   ], 1);
    ASSERT_EQ(outputs[UP2   ], 0);
    ASSERT_EQ(outputs[UP3   ], 0);
    ASSERT_EQ(outputs[UP4   ], 0);
    ASSERT_EQ(outputs[ZV5   ], 0);
    ASSERT_EQ(outputs[UP6   ], 0);
    ASSERT_EQ(outputs[UP7   ], 0);
    ASSERT_EQ(outputs[UP8   ], 0);
    ASSERT_EQ(outputs[KESSEL], 0);
    ASSERT_EQ(outputs[ZV3a  ], 0);
    ASSERT_EQ(outputs[ZV4a  ], 0);
    ASSERT_EQ(outputs[ALARM ], 0);

    // test dropping F2
    t[F2] = _F3 + D1 - 1;  
    loop_heizung();
    ASSERT_EQ(outputs[UP1   ], 1); // still ok because of hysterese
    t[F2] = _F3 + D1 - 2; 
    loop_heizung();
    ASSERT_EQ(outputs[UP1   ], 0);  // F2 to low now
}


TEST_F(HeizungsTest, Direktheizung_Solar_1) {

    int _F3 = 50;
    int temperatures[PTC_NR] = {
        _F3 + D2 - 3, // Sonnenfühler
        _F3 + D1 - 3, // Kollektorfühler
        _F3, // Boilerfühler unten
        20, // Pufferfühler Sektion 1
        30, // Pufferfühler Sektion 2
        40, // Pufferfühler Sektion 3
        35, // Heizung Rücklauffühler
        20, // Festbrennstoffkesselfühler
        30, // Pufferfühler mitte
        45, // Pufferfühler oben
        60, // Boilerfühler oben
        F12min - 10   // Außentempteraturfühler
    };
    memcpy(t, temperatures, sizeof(temperatures));
    loop_heizung();
    print_state();
    ASSERT_EQ(outputs[UP1   ], 0);
    ASSERT_EQ(outputs[UP2   ], 0);
    ASSERT_EQ(outputs[UP3   ], 0);
    ASSERT_EQ(outputs[UP4   ], 0);
    ASSERT_EQ(outputs[ZV5   ], 1);
    ASSERT_EQ(outputs[UP6   ], 1);
    ASSERT_EQ(outputs[UP7   ], 0);
    ASSERT_EQ(outputs[UP8   ], 0);
    ASSERT_EQ(outputs[KESSEL], 0);
    ASSERT_EQ(outputs[ZV3a  ], 0);
    ASSERT_EQ(outputs[ZV4a  ], 0);
    ASSERT_EQ(outputs[ALARM ], 0);
}
