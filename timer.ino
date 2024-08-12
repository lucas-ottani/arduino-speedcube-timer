#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define button1 12
#define button2 13
#define led 8

#define connection 0x27
#define columns 16
#define rows 2

LiquidCrystal_I2C lcd(connection, columns, rows);

float timer = 0;

// Variable to avoid entering the loop after finishing the solve
bool verify_loop = true;

// Millis() variables
unsigned long previousMillis = 0;
const long interval = 20; // 10 = 0.01 seconds

void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(led, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  if (digitalRead(button1) == 1 && digitalRead(button2) == 1 && verify_loop) {
    verify_loop = false;
    timer = 0;
    delay(150);
    digitalWrite(led, HIGH);

    // Start the timer until both buttons are pressed simultaneously.
    while (!(digitalRead(button1) == 1 && digitalRead(button2) == 1)) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        lcd.setCursor(6, 1);
        lcd.print(timer);
        timer = timer + 0.02;
        previousMillis = currentMillis;
      }
    }
    // Return 'verify_loop' to true to allow starting the timer after finishing the solve.
    verify_loop = true;
    digitalWrite(led, LOW); 
    delay(150);
  }
}
