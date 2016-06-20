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
	public:

		/**
		 * A struct containing the position of the Disk (determined by the
		 * HallSensor and the time when this position has been determined.
		 */
		struct DiskPosition {

			/**
			 * The "after" value of the last slope (0->1 means position is ONE,
			 * which represents the oposite site of the hole, 1->0 means
			 * position is ZERO), which represents the position  direct in top
			 * of the hole.)
			 */
			Sensor::Value value;

			/**
			 * The time when this value has been recorded, i.e. the slope
			 * occured.
			 */
			unsigned long time;
		};

	private:
		/**
		 * The number of samples taken from the Photosensor.
		 */
		static const unsigned short _pSensorSampleSize = 12;

		/**
		 * Bool indicating whether the disk is stable.
		 */
		bool _stable;

		/**
		 * Bool indicating whether the disk is on the correct side.
		 *
		 * \todo Unclear whether this is one is needed.
		 */
		bool _westside;

		/**
		 * Pointer to the PhotoSensor instance.
		 */
		PhotoSensor* _pSensor;

		/**
		 * Pointer to the HallSensor instance.
		 */
		HallSensor* _hSensor;

		/**
		 * The "after" value of the last slope of the PhotoSensor (0->1 means
		 * position is ONE, 1->0 means position is ZERO).
		 */
		Sensor::Value _pSensorLastValue;

		/**
		 * The last sample values from the PhotoSensor. The array is used as a
		 * ring buffer.
		 */
		unsigned long _pSensorLastTimes[_pSensorSampleSize];

		/**
		 * Index of the newest element in the ring buffer of PhotoSensor sample
		 * values.
		 */
		unsigned short _timeIndex;

		/**
		 * The last recorded HallSensor slope, i.e. the last recorded disk
		 * position.
		 */
		DiskPosition _position;

	public:

		/**
		 * Class constructor.
		 *
		 * \param ps Instance of the photo sensor.
		 * \param hs Instance of the hall sensor.
		 */
		inline Disk(PhotoSensor* ps, HallSensor* hs) : _stable(false),
			_westside(false), _pSensor(ps), _hSensor(hs),
			_pSensorLastValue(Sensor::Value::INVALID), _pSensorLastTimes{ },
			_timeIndex(0), _position{Sensor::Value::INVALID, 0} {}

		/**
		 * Checks whether the disk is stable.
		 *
		 * \return True if the disk is stable, else false.
		 */
		//inline bool isStable() { return _stable; }
		inline bool isStable() { return true; }

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

		inline DiskPosition position() { return _position; }
};
