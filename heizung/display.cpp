#include "Arduino.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"

#include "display.h"
#include "heizung.h"

LiquidCrystal_I2C lcd0(0x27, 20, 4);
LiquidCrystal_I2C lcd1(0x26, 20, 4);
LiquidCrystal_I2C lcd2(0x25, 20, 4);

bool lcd_enabled = false;

void setup_lcd(void)
{
    lcd_enabled = true;
    lcd0.init();
    lcd0.backlight();
    lcd1.init();
    lcd1.backlight();
    lcd2.init();
    lcd2.backlight();
}

void lcd_print(LiquidCrystal_I2C *lcd, char *line0, char *line1, char *line2, char *line3)
{
    lcd->setCursor(0,0);
    lcd->print(line0);
    lcd->setCursor(0,1);
    lcd->print(line1);
    lcd->setCursor(0,2);
    lcd->print(line2);
    lcd->setCursor(0,3);
    lcd->print(line3);
}

void display(int *t)
{
    char line0[21];
    char line1[21];
    char line2[21];
    char line3[21];

#ifdef ENABLE_LCD
    if (lcd_enabled) {
        // print temperatures on LCD 0
        sprintf(line0, "F1:  %3d C          ", t[0]);
        sprintf(line1, "F2:  %3d C          ", t[1]);
        sprintf(line2, "F3:  %3d C          ", t[2]);
        sprintf(line3, "F4:  %3d C          ", t[3]);
        lcd_print(&lcd0, line0, line1, line2, line3);

        // print temperatures on LCD 1
        sprintf(line0, "F5:  %3d C          ", t[4]);
        sprintf(line1, "F6:  %3d C          ", t[5]);
        sprintf(line2, "F7:  %3d C          ", t[6]);
        sprintf(line3, "F8:  %3d C          ", t[7]);
        lcd_print(&lcd1, line0, line1, line2, line3);

        // print temperatures on LCD 2
        sprintf(line0, "F9:  %3d C          ", t[8]);
        sprintf(line1, "F10: %3d C          ", t[9]);
        sprintf(line2, "F11: %3d C          ", t[10]);
        sprintf(line3, "F12: %3d C          ", t[11]);
        lcd_print(&lcd2, line0, line1, line2, line3);
    }
#endif // ENABLE_LCD

#ifdef ENABLE_SERIAL
    // print temperatures via serial connection
    for (int i = 0; i < PTC_NR; i++) {
        Serial.print("PTC ID ");
        Serial.print(i);
        Serial.print(" :");
        Serial.print(t[i]);
        Serial.println(" C");
    }
#endif // ENABLE_SERIAL
}
