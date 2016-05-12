/**
 * @file
 *
 * The header file of the Sensor class.
 */

#pragma once

#include "component.h"

/**
 * A hardware sensor, i.e. a component reading environment values.
 */
class Sensor : public Component {
	protected:

		/**
		 * Class constructor.
		 *
		 * \param pin The number of the pin connected to the sensor.
		 */
		inline Sensor(unsigned short pin) : Component(pin) {}

	public:

		/**
		 * Method reading binary values from the sensor.
		 *
		 * \return The (binary) value of the sensor.
		 */
		inline bool read() { return digitalRead(_pin); }
};
