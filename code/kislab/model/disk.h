/**
 * @file
 *
 * The header file of the Disk class.
 */

#pragma once

#include "../hardware/hallsensor.h"
#include "../hardware/photosensor.h"
#include "../hardware/release.h"

/**
 * A model for the disk.
 *
 * \todo Add direction (of rotation) as class member.
 */
class Disk {
	private:

		/**
		 * Bool indicating whether the disk is stable.
		 */
		bool _stable = false;

		/**
		 * Bool indicating whether the disk is on the correct side.
		 *
		 * \todo Unclear whether this is one is needed.
		 */
		bool _westside = false;

		/**
		 * Speed of the disk.
		 *
		 * \todo
		 * meassured in average millis ?!
		 * see https://www.arduino.cc/en/Reference/Millis
		 * Do we keep it as value or calc it on the fly?
		 */
		float _speed = 0;

		/**
		 * Pointer to the PhotoSensor instance.
		 */
		PhotoSensor* _pSensor;

		/**
		 * Pointer to the HallSensor instance.
		 */
		HallSensor* _hSensor;

	public:

		/**
		 * Class constructor.
		 *
		 * \param ps Instance of the photo sensor.
		 * \param hs Instance of the hall sensor.
		 */
		inline Disk(PhotoSensor* ps, HallSensor* hs) : _pSensor(ps),
				_hSensor(hs) {}

		/**
		 * Checks whether the disk is stable.
		 *
		 * \return True if the disk is stable, else false.
		 */
		inline bool isStable() { return _stable; }
};
