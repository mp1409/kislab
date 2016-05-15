/**
 * @file
 *
 * Header file of the Component class.
 */

#pragma once

#include "Arduino.h"

/**
 * A hardware component which is accesible by the Arduino.
 */
class Component {
	protected:

		/**
		 * The number of the pin connected to the component.
		 */
		const unsigned short _pin;

		/**
		 * Class constructor.
		 *
		 * \param pin The number of the pin connected to the component.
		 */
		Component(unsigned short pin) : _pin(pin) {}
};
