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
 * The basic design principle of this class is that the output values (e.g. the
 * duration of a rotation or the disk poistion) are calculated from the internal
 * state of the class. The internal state is updated by a non-blocking method.
 * By this, a clear seperation between polling sensors and return of values is
 * established.
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
		 * Pointer to the PhotoSensor instance.
		 */
		PhotoSensor* _pSensor;

		/**
		 * The number of samples taken from the Photosensor.
		 */
		static const unsigned short _pSensorSampleSize = 12;

		/**
		 * Pointer to the HallSensor instance.
		 */
		HallSensor* _hSensor;

		/**
		 * The number of samples taken from the HallSensor.
		 */
		static const unsigned short _hSensorSampleSize = 2;

		short _lastSlope = -1;

		/**
		 * The last sample values from the PhotoSensor. The array is used as a
		 * ring buffer.
		 */
		unsigned long _pSensorLastTimes[_pSensorSampleSize] = { };

		/**
		 * Index of the newest element in the ring buffer of PhotoSensor sample
		 * values.
		 */
		unsigned short _timeIndex = 0;

		/**
		 * The last recorded position of the hall sensor.
		 */
		struct {
			short position = -1;
			unsigned long lastTime = 0;
		} _hSensorPosition;
	

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

		/**
		 * Update the internal state by polling the sensors. Immediately return
		 * the control flow.
		 */
		void update();

		/**
		 * Return the number of milliseconds per disk rotation. The number is
		 * calculated from the latest measurement values that have been obtained
		 * by the update method.
		 *
		 * \return Number of milliseconds per disk rotation, 0 if in warmup
		 * state.
		 */
		double millisPerRot();
};
