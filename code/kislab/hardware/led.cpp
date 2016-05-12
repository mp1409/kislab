/**
 * @file
 *
 * The implmentation file of the LED class.
 */

#include "led.h"

#include "Arduino.h"

void LED::set(bool state) {
	_state = state;

	if (state) {
		digitalWrite(_pin, HIGH);
	} else {
		digitalWrite(_pin, LOW);
	}
}
