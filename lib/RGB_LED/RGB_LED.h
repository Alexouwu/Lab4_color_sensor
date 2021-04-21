#ifndef _RGB_LED_H
#define _RGB_LED_H

#include <Arduino.h>
#include "PWM_ESP32.h"

#define RED 0
#define GREEN 1
#define BLUE 2

class RGB_LED
{
private:
    /* data */
    PWM leds[3];
public:
    RGB_LED();
    ~RGB_LED();
    void begin(const byte pins[3], byte channels[3], bool on_state, double frequency = 1000, uint8_t bit_resolution = 8);
    void setColor(byte red, byte green, byte blue);
};


#endif