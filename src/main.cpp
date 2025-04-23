#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

double timer = 10;
bool game_stop = false;
unsigned long lastButtonPressTime = 0;	 // Debounce timer
const unsigned long debounceDelay = 200; // Milliseconds to debounce

void setup()
{
	lcd.init();
	lcd.backlight();

	pinMode(12, INPUT_PULLUP);
}

void loop()
{
	unsigned long currentMillis = millis();

	// Game Running
	if (!game_stop)
	{
		lcd.clear();
		lcd.print("Arduino Game!");
		lcd.setCursor(6, 1);
		lcd.print(timer, 2); // Display with 1 decimal place

		// Button press handling with debounce
		if (digitalRead(12) == LOW && currentMillis - lastButtonPressTime > debounceDelay)
		{
			game_stop = true;
			lcd.clear();
			lastButtonPressTime = currentMillis;
		}

		// Timer countdown
		if (timer > 0)
		{
			delay(2);
			timer -= 0.02;
		}
		else
		{
			timer = 10; // Reset timer after it reaches zero
		}
	}
	// Game Over
	else
	{
		lcd.setCursor(0, 0);
		lcd.print("Game Over!");
		lcd.setCursor(0, 1);
		lcd.print("Your time: ");
		lcd.print(timer, 1); // Display with 1 decimal place

		// Button press to restart the game
		if (digitalRead(12) == LOW && currentMillis - lastButtonPressTime > debounceDelay)
		{
			game_stop = false;
			lcd.clear();
			timer = 10; // Reset timer to initial value
			lastButtonPressTime = currentMillis;
		}
	}
}