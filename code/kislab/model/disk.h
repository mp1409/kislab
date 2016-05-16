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
		bool westside; // bool die indiziert ob die scheibe sich grade auf der richtigen seite zum fallen befindet
		float speed; // geschwindikgeit der scheibe
		Release* release;
		PhotoSensor* pSensor;
		HallSensor* hSensor;

	public:

		/**
		 * Class constructor
		 */
		Disk(PhotoSensor*, HallSensor*);
		~Disk();

		inline bool getState() { return stable; }

		inline void go();
};
