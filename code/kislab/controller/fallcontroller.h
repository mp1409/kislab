/**
 * @file
 *
 * The header file of the FallController class.
 */

#pragma once

#include "controller.h"
#include "../model/disk.h"
#include "../hardware/trigger.h"

/**
 * This is a controller for the release of (several) bullets after the trigger
 * has been pressed.
 */
class FallController : public Controller {
	private:

		/**
		 * Pointer to the disk instance.
		 */
		Disk* _disk;

		/**
		 * Pointer to the trigger instance.
		 */
		Trigger* _trigger;

		/**
		 * Calculates the next bullet release time, based on current values from
		 * the disk.
		 *
		 * \return The next possible bullet release time.
		 */
		unsigned long calculateNextReleaseTime();

		unsigned int _defaultPollInterval;

	public:

		/**
		 * Class constructor.
		 *
		 * \param disk Pointer to the Disk instance.
		 * \param trigger Pointer to the Trigger instance.
		 */
		inline FallController(Disk* disk, Trigger* trigger) : _disk(disk),
				_trigger(trigger), _defaultPollInterval(10) {}

		void run();

		void debug();
};
