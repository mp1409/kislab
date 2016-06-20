/**
 * @file
 *
 * The header file of the DebugController class.
 */

#pragma once

#include "controller.h"
#include "../model/disk.h"

/**
 * This is a controller for debugging purposes.
 */
class DebugController : public Controller {
	private:

		/**
		 * Pointer to the disk instance.
		 */
		Disk* _disk;

	public:

		/**
		 * Class constructor.
		 *
		 * \param disk Pointer to the Disk instance.
		 */
		inline explicit DebugController(Disk* disk) : _disk(disk) {}

		void run();
};
