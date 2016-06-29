/**
 * @file
 *
 * The header file of the FallController class.
 */

#pragma once

#include "controller.h"
#include "../hardware/trigger.h"
#include "../hardware/release.h"
#include "../model/disk.h"

/**
 * This is a controller for the release of (several) bullets after the trigger
 * has been pressed.
 *
 * \todo When there are several things to poll (disk, trigger), consolidate them
 * into an update method.
 *
 * \todo Allow multiple trigger presses (store them in a variable)
 */
class FallController : public Controller {
	private:

		/**
		 * The default poll interval (for example for the disk).
		 */
		const unsigned int _pollInterval = 10;

		const unsigned int _triggerCooldown = 100;

		/**
		 * Pointer to the disk instance.
		 */
		Disk* _disk;

		/**
		 * Pointer to the release instance.
		 */
		Release* _release;

		/**
		 * Pointer to the trigger instance.
		 */
		Trigger* _trigger;

		Sensor::Value _lastTriggerState;
		unsigned long _lastTriggerTime;

		unsigned short _triggerCount;

		/**
		 * Calculates the next bullet release time, based on current values from
		 * the disk.
		 *
		 * \return The next possible bullet release time.
		 */
		unsigned long calculateNextReleaseTime();

		void update();

		/**
		 * Release a ball while continuing to update the interal states.
		 */
		void releaseTheKraken();

	public:

		/**
		 * Class constructor.
		 *
		 * \param disk Pointer to the Disk instance.
		 * \param release Pointer to the Release instance.
		 * \param trigger Pointer to the Trigger instance.
		 */
		inline FallController(Disk* disk, Release* release, Trigger* trigger) :
				_disk(disk), _release(release), _trigger(trigger), _lastTriggerState(Sensor::Value::INVALID), _triggerCount(0) {}

		void run();
};
