/**
 * @file
 *
 * The header file of the ManualRelease class.
 */

#pragma once

#include "controller.h"
#include "../hardware/trigger.h"
#include "../hardware/release.h"

/**
 * This is a controller for the manual (i.e. direct) release of a bullet after
 * the trigger has been pressed, making it kind of a game.
 */
class ManualRelease : public Controller {
	private:
		/**
		 * The default poll interval for the trigger.
		 */
		const unsigned int _pollInterval = 10;

		/**
		 * Pointer to the release instance.
		 */
		Release* _release;

		/**
		 * Pointer to the trigger instance.
		 */
		Trigger* _trigger;

		/**
		 * Release a ball.
		 */
		void releaseTheKraken();

	public:

		/**
		 * Class constructor.
		 *
		 * \param release Pointer to the Release instance.
		 * \param trigger Pointer to the Trigger instance.
		 */
		inline ManualRelease(Release* release, Trigger* trigger) :
				_release(release), _trigger(trigger) {}

		void run();
};
