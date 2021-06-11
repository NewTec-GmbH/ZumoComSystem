/**
 * @file main.cpp
 * @author Luis Moser
 * @brief Simple blink test program for the ESP32
 * @date June 2021
 */
#include <Arduino.h>

/** LED pin definition **/
#define LED 2

/**
 * Setup function which initializes the ESP32
 */
void setup()
{
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

/**
 * Loop function which represents the super-loop
 */
void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}