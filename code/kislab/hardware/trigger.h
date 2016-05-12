/**
 * @file
 *
 * Header file of the Trigger class.
 */

#pragma once

#include "sensor.h"

/**
 * The trigger.
 */
class Trigger : public Sensor {
	public:

		/**
		 * Class constructor.
		 */
		inline Trigger() : Sensor(4) {}
};
