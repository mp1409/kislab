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
 */
class FallController : public Controller {
	private:

		/**
		 * The default poll interval (for example for the disk).
		 */
		const unsigned int _pollInterval = 10;

		/**
		 * The delay between two independent trigger press events.
		 */
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

		/**
		 * The last recorded state of the trigger.
		 */
		Sensor::Value _lastTriggerState;

		/**
		 * The time when the last trigger reading happened.
		 */
		unsigned long _lastTriggerTime;

		/**
		 * The number of unprocessed trigger events.
		 */
		unsigned short _triggerCount;

		/**
		 * Calculates the next bullet release time, based on current values
		 * from the disk.
		 *
		 * \return The next possible bullet release time.
		 */
		unsigned long calculateNextReleaseTime();

		/**
		 * Update the internal state (concerning the trigger) and the state of
		 * the disk.
		 */
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
				_disk(disk), _release(release), _trigger(trigger),
				_lastTriggerState(Sensor::Value::INVALID), _lastTriggerTime(0),
				_triggerCount(0) {}

		void run();
};
