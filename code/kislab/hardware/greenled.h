/**
 * @file
 *
 * Header file of the GreenLED class.
 */

#pragma once

#include "led.h"

/**
 * The green LED mounted directly on the Arduino.
 */
class GreenLED : public LED {
	public:

		/**
		 * Class constructor.
		 */
		inline GreenLED() : LED(13) {}
};
