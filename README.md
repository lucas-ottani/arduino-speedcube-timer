# arduino-speedcube-timer

This is a stack timer project used in speedcubing. Buttons were used instead of proximity sensors.

The display was an I2C device, LiquidCrystal_I2C library is mandatory for the LCD display and Wire for I2C communication.

The time runs at 0.2s speed due to limitations in Arduino Uno CPU power, even when Millis() is used. It probably works better with RTC module to avoid time inaccuracies.
