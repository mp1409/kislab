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
 */
class Disk {

	private:

		/**
		 * Bool indicating whether the disk is stable.
		 */
		bool stable;

		/**
		 * Bool indicating whether the disk is on the correct side.
		 *
		 * \todo Unclear whether this is one is needed.
		 */
		bool westside;

		/**
		 * Speed of the disk.
		 */
		float speed;

		/**
		 * Pointer to the Release instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		Release* release;

		/**
		 * Pointer to the PhotoSensor instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		PhotoSensor* pSensor;

		/**
		 * Pointer to the HallSensor instance.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		HallSensor* hSensor;

	public:

		/**
		 * Class constructor.
		 */
		Disk(PhotoSensor*, HallSensor*);
		~Disk();

		/**
		 * Checks whether the disk is stable.
		 *
		 * \return True if the disk is stable, else false.
		 */
		inline bool getState() { return stable; }

		/**
		 * Method to let the disk run and the ball fall.
		 *
		 * \todo Unclear whether this is needed here, i.e. does it make sense
		 * that the Disk class controls the relase?
		 */
		inline void go();
};
