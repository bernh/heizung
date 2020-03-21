#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "display.h"
#include "heizung.h"

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup_lcd(void)
{
    lcd.init();
    lcd.backlight();
}

void display(int *t)
{
    // print temperatures on LCD 
    char line0[21];
    char line1[21];
    char line2[21];
    char line3[21];

    sprintf(line0, "F1 %-3d F2 %-3d F3 %-3d", t[0], t[1], t[2]);
    sprintf(line1, "F4 %-3d F5 %-3d F6 %-3d", t[3], t[4], t[5]);
    sprintf(line2, "F7 %-3d F8 %-3d F9 %-3d", t[6], t[7], t[8]);
    sprintf(line3, "10 %-3d 11 %-3d 12 %-3d", t[9], t[10], t[11]);
    lcd.setCursor(0,0);
    lcd.print(line0);
    lcd.print(line1);
    lcd.print(line2);
    lcd.print(line3);

    // print temperatures via serial connection
    for (int i = 0; i < PTC_NR; i++) {
        Serial.print("PTC ID ");
        Serial.print(i);
        Serial.print(" :");
        Serial.print(t[i]);
        Serial.println(" C");
    }
}
