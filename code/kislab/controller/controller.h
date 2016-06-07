/**
 * @file
 *
 * The header file of the Controller class.
 */

#pragma once

/**
 * An abstract base class for a controller. A controller is a module that -
 * after being invoked by the run method of the subclass instances - takes and
 * manages the control flow of the system. The main logic concerning the order
 * of events remains here. The control flow should only leave this module for
 * short pollings and non-blocking method calls in other components.
 */
class Controller {
	public:

		/**
		 * Takes over the control flow and runs continuously.
		 */
		virtual void run() = 0;
};
