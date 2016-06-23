/**
 * @file
 *
 * The header file of the Release class.
 */

#pragma once

#include "component.h"

#include <Servo.h>

/**
 * The component responsible for releasing bullets.
 *
 * \todo Open/Close slowly? add a move method
 */
class Release : public Component {

	private:
		/**
		 * Instance of the servo motor.
		 */
		Servo _servo;

	public:

		/**
		 * Class constructor. Ensures that the Release is closed.
		 */
		Release();

		/**
		 * Opens the release.
		 */
		inline void open() { _servo.write(20); }

		/**
		 * Closes the release.
		 */
		inline void close() { _servo.write(0); }
};
