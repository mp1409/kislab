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
		 */
		float _speed = 0;

		/**
		 * Pointer to the Release instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		Release* _release;

		/**
		 * Pointer to the PhotoSensor instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		PhotoSensor* _pSensor;

		/**
		 * Pointer to the HallSensor instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		HallSensor* _hSensor;

	public:

		/**
		 * Class constructor.
		 *
		 * \param ps Instance of the photo sensor.
		 * \param hs Instance of the hall sensor.
		 * \param r Instance of the release.
		 */
		inline Disk(PhotoSensor* ps, HallSensor* hs, Release* r) : _release(r),
				_pSensor(ps), _hSensor(hs) {}

		/**
		 * Checks whether the disk is stable.
		 *
		 * \return True if the disk is stable, else false.
		 */
		inline bool isStable() { return _stable; }

		/**
		 * Method to let the ball fall.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		void go();
};
