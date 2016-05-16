/**
 * @file
 *
 * The header file of the Disk class.
 */

#pragma once

#include "../hardware/hallsensor.h"
#include "../hardware/release.h"
#include "../hardware/photosensor.h"

/**
 * The component responsible for releasing bullets.
 */
class Disk {

	private:
		bool stable;
		Release* release;
		PhotoSensor* pSensor;
		HallSensor* hSensor;

	public:

		/**
		 * Class constructor
		 */
		Disk();
		~Disk();

		inline bool getState() { return stable; }

		inline void go();
};