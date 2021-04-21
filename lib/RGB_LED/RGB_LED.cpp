#include "RGB_LED.h"

RGB_LED::RGB_LED()
{
}

RGB_LED::~RGB_LED()
{
}

void RGB_LED::begin(const byte pins[3], byte channels[3], bool on_state, double frequency, uint8_t bit_resolution)
{
    for (byte i = RED; i <= BLUE; i++)
        leds[i].setup(pins[i], channels[i], frequency, bit_resolution, on_state); 
}

void RGB_LED::setColor(byte red, byte green, byte blue)
{
    leds[RED].setDigitalLevel(red);
    leds[GREEN].setDigitalLevel(green);
    leds[BLUE].setDigitalLevel(blue);
}