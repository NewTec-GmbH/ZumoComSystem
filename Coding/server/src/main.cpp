/**
 * @file main.cpp
 * @author Luis Moser
 * @brief Simple blink test program for the ESP32
 * @date 06/14/2021
 * 
 * @{
 */
#include <Logger.h>

/**
 * Setup function which initializes the ESP32
 */
void setup()
{
    Serial.begin(9600);
}

/**
 * Loop function which represents the super-loop
 */
void loop()
{
    Log &log = Log::getInstance();

    log.setLogLevel(Log::LEVEL_DEBUG);

    Log::LogLevel level = log.getLogLevel();

    Serial.println(level);

    LOG_DEBUG("This is a debug");
    LOG_INFO("This is an info");
    LOG_WARN("This is a warning");
    LOG_ERROR("This is an error!");
    LOG_DEBUG("");
    LOG_DEBUG("next");

    delay(1000);
}