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
		 * Pointer to the PhotoSensor instance.
		 */
		PhotoSensor* _pSensor;
		static const unsigned short _pSensorSampleSize = 12;

		/**
		 * Pointer to the HallSensor instance.
		 */
		HallSensor* _hSensor;
		static const unsigned short _hSensorSampleSize = 2;

		short _lastSlope = -1;
		short _timeIndex = 0;
		unsigned long _pSensorLastTimes[_pSensorSampleSize] = { };
		
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
		void update();
		double millisPerRot();
};
