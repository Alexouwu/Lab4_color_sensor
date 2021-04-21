#include "PWM_ESP32.h"

PWM::PWM()
{
}

PWM::~PWM()
{
	detachPin(_pin);
}

void PWM::setup(uint8_t pin, uint8_t channel, double frequency, uint8_t bit_resolution, bool on_state)
{
	_pin = pin;
	_channel = channel;
	_frequency = frequency;
	_digital_range = pow(2, bit_resolution) - 1;
	pinMode(pin, OUTPUT);
	ledcSetup(_channel, _frequency, bit_resolution);
	attachPin(_pin, on_state);
	setDuty(0);
}

void PWM::setDuty(float duty_cycle)
{
	if (duty_cycle > 100)
		duty_cycle = 100;
	else if (duty_cycle < 0)
		duty_cycle = 0;
	setDigitalLevel((_digital_range * duty_cycle) / 100);
}

void PWM::setDigitalLevel(uint32_t level)
{
	if (level > _digital_range)
		level = _digital_range;
	_duty_cycle = (level * 100.0f) / _digital_range;
	ledcWrite(_channel, level);
}

void PWM::setFrequency(float frequency)
{
	_frequency = frequency;
	ledcWriteTone(_channel, _frequency);
}

void PWM::attachPin(uint8_t pin, bool on_state)
{
	pinMode(pin, OUTPUT);
	ledcAttachPin(pin, _channel);	
	if (on_state == LOW)
		GPIO.func_out_sel_cfg[pin].inv_sel = 1;
}

void PWM::detachPin(uint8_t pin)
{
	ledcDetachPin(pin);
	GPIO.func_out_sel_cfg[pin].inv_sel = 0;
}