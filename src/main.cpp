#include <Arduino.h>
#include "ADC_Read.h"
#include "RGB_LED.h"
#include "PWM_ESP32.h"
//objects
ADC adc_ldr;
RGB_LED led_rgb;
String data_in;
//variables
const byte pins[3] = {12, 14, 27};
byte channels[3] = {0, 1, 2};
const byte ADC_PIN = 25; //Constantes snake case en mayusculas
uint16_t led_on_time = 200;
uint16_t reads[3];
ulong start_time;
byte states;

void setup()
{
  Serial.begin(115200); //La computadora espera 9600
  adc_ldr.begin(ADC_PIN, 12, 3.3F);
  led_rgb.begin(pins, channels, HIGH);
  states = RED;
  led_rgb.setColor(255, 0, 0);
  start_time = millis();
  //led_rgb.setup(pins, chan, 10000, 12);
}

void loop()
{

  if (millis() - start_time > led_on_time)
  {
    switch (states)
    {
    case RED:
      reads[RED] = adc_ldr.readRaw();
      states = GREEN;
      led_rgb.setColor(0, 255, 0);
      break;

    case GREEN:
      reads[GREEN] = adc_ldr.readRaw();
      states = BLUE;
      led_rgb.setColor(0, 0, 255);
      break;

    case BLUE:
      reads[BLUE] = adc_ldr.readRaw();
      Serial.printf("%d,%d,%d \n", reads[RED], reads[GREEN], reads[BLUE]);
      states = RED;
      led_rgb.setColor(255, 0, 0);
      break;
    }
    start_time = millis();
  }

  if (Serial.available())
  {
    data_in = Serial.readStringUntil('\n');
    led_on_time = data_in.toInt();
  }
  
}