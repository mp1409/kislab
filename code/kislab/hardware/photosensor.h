/**
 * @file
 *
 * Header file of the PhotoSensor class.
 */

#pragma once

#include "sensor.h"

/**
 * A photo sensor, reacting to color changes on the lower side of the disc.
 */
class PhotoSensor : public Sensor {
	public:

		/**
		 * Class constructor.
		 */
		inline PhotoSensor() : Sensor(2) {}

		inline String name() { return String("PhotoSensor"); }
};
