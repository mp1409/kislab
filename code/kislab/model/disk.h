/**
 * @file
 *
 * The header file of the Disk class.
 */

#pragma once

#include "hallsensor.h"
#include "release.h"
#include "photosensor.h"

/**
 * The component responsible for releasing bullets.
 */
class Disk {

	private:
		bool stable;
		Release release = new Release();

	public:

		/**
		 * Class constructor
		 */
		Disk();

		inline bool getState() { return stable; }

		inline void go();
};
