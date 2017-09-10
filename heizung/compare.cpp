#include "heizung.h"
#include "compare.h"

int F2_bigger_F3_plus_D1(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F3] + D1, t[F2], hysterese, state);
    return state;
}

int F3_smaller_F3max(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F3], F3max, hysterese, state);
    return state;
}

int F1_smaller_F3_plus_D2(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F1], t[F3] + D2, hysterese, state);
    return state;
}

int F12_smaller_F12min(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F12], F12min, hysterese, state);
    return state;
}

int F2_smaller_F7_plus_D12(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F2], t[F7] + D12, hysterese, state);
    return state;
}

int F2_bigger_F7_plus_D3(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F7] + D3, t[F2], hysterese, state);
    return state;
}

int F2_bigger_F4_plus_D4(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F4] + D4, t[F2], hysterese, state);
    return state;
}

int F4_smaller_F4max(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F4], F4max, hysterese, state);
    return state;
}

int F1_smaller_F4_plus_D5(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F1], t[F4] + D5, hysterese, state);
    return state;
}

int F2_bigger_F5_plus_D6(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F5] + D6, t[F2], hysterese, state);
    return state;
}

int F5_smaller_F5max(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F5], F5max, hysterese, state);
    return state;
}

int F1_smaller_F5_plus_D7(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F1], t[F5] + D7, hysterese, state);
    return state;
}

int F2_bigger_F6_plus_D8(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F6] + D8, t[F2], hysterese, state);
    return state;
}

int F6_smaller_F6max(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F6], F6max, hysterese, state);
    return state;
}

int F2_smaller_F7_plus_D13(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F2], t[F7] + D13, hysterese, state);
    return state;
}

int F10_smaller_F7_plus_D13(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F10], t[F7] + D13, hysterese, state);
    return state;
}

int F10_bigger_F11_plus_D9(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F11] + D9, t[F10], hysterese, state);
    return state;
}

int F11_smaller_F11max(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F11], F11max, hysterese, state);
    return state;
}

int F8_bigger_F8min(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (F8min, t[F8], hysterese, state);
    return state;
}

int F8_bigger_F11_plus_D9(int *t)
{
    static int state = 0;     // initial state
    static int hysterese = 1; // plus minus
    state = compare (t[F11] + D9, t[F8], hysterese, state);
    return state;
}



int compare(int v1, int v2, int hysterese, int state) {
    // Vergleich v1 < v2 mit berücksichtigung von hysterese und status
    if (state == 0) {
        // v1 bis jetzt größer als v2, muss um mindestens die Hysterese kleiner
        // sein
        return (v1 < (v2 - hysterese));
    } else {
        // v1 bis jetzt kleiner als v2, bleibt kleiner solange um weniger als
        // die Hysterese größer
        return (v1 <= (v2 + hysterese));
    }
}
