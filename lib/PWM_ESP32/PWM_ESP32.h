#ifndef _PWM_ESP32_h
#define _PWM_ESP32_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PWM
{
public:
	PWM();
	~PWM();
	void setup(uint8_t pin, uint8_t channel, double frequency, uint8_t bit_resolution, bool on_state = HIGH);
	void setDuty(float duty_cycle);
	void setDigitalLevel(uint32_t level);
	void setFrequency(float frequency);
	void attachPin(uint8_t pin, bool on_state = HIGH);
	void detachPin(uint8_t pin);

protected:
	uint8_t _pin;
	uint8_t _channel;
	uint32_t _digital_range;
	float _duty_cycle;
	float _frequency;
};

#endif