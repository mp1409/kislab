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
	public:

		/**
		 * The different values a sensor reading can have.
		 */
		enum Value {
			ZERO = 0, /**< The sensor returned 0. **/
			ONE = 1, /**< The sensor returned 1. **/
			INVALID = 2 /**< The sensor reading is not valid or present. **/
		};

	protected:

		/**
		 * Class constructor.
		 *
		 * \param pin The number of the pin connected to the sensor.
		 */
		inline explicit Sensor(unsigned short pin) : Component(pin) {}

	public:

		/**
		 * Method returning a descriptive name of the sensor.
		 *
		 * \return The sensor's name.
		 */
		virtual String name() = 0;

		/**
		 * Method reading binary values from the sensor.
		 *
		 * \return The (binary) value of the sensor.
		 */
		inline Value read() { return static_cast<Value>(digitalRead(_pin)); }
};
