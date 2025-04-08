#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

double timer = 10;

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  lcd.clear();
  lcd.print("Arduino Game!");
  lcd.setCursor(6, 1);
  lcd.print(timer);
  if (timer > 0)
  {
    delay(4);
    timer -= 0.01;
  }
  else
  {
    timer = 10;
  }
}
