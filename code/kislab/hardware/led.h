/**
 * @file
 *
 * The header file of the LED class.
 */

#pragma once

#include "component.h"

/**
 * A LED.
 */
class LED : public Component {
	private:

		/**
		 * The state of the LED. True means that the LED emits light, false
		 * means that it is switched off. MUST ONLY be set via the set method,
		 * else the state will not be flushed to the hardware.
		 */
		bool _state;

	protected:

		/**
		 * Class constructor. The LED is initally off.
		 *
		 * \param pin The number of the pin connected to the LED.
		 */
		inline LED(unsigned short pin) : Component(pin) { set(false); }

	public:

		/**
		 * Sets the state of the LED.
		 *
		 * \param state The new state of the LED.
		 */
		void set(bool state);

		/**
		 * Switch the LED on.
		 */
		inline void on() { set(true); }

		/**
		 * Switch the LED off.
		 */
		inline void off() { set(false); }

		/**
		 * Switch the LED on, when it was off before, and vice versa.
		 */
		inline void toggle() { set(not state()); }

		/**
		 * Get the current state.
		 *
		 * \return The current state of the LED.
		 */
		inline bool state() { return _state; }
};
