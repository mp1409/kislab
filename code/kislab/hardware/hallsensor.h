/**
 * @file
 *
 * Header file of the HallSensor class.
 */

#pragma once

#include "sensor.h"

/**
 * A hall sensor, triggered by magnets on the disc.
 */
class HallSensor : public Sensor {
	public:

		/**
		 * Class constructor.
		 */
		inline HallSensor() : Sensor(3) {}
};
