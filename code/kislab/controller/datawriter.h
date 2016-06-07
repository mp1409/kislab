/**
 * @file
 *
 * The header file of the DataWriter class.
 */

#pragma once

#include "controller.h"
#include "../hardware/sensor.h"

/**
 * A controller writing sensor values to the serial output.
 */
class DataWriter : public Controller {
	private:

		/**
		 * Array of pointers to all of the sensors to write to serial output.
		 */
		Sensor** _sensors;

		/**
		 * Number of sensors (size of the sensor array).
		 */
		unsigned int _numSensors;

	public:

		/**
		 * Class constructor. Writes the CSV header.
		 *
		 * \param sensors Array of pointers of sensors.
		 * \param numSensors Size of the array.
		 */
		DataWriter(Sensor** sensors, unsigned int numSensors);

		/**
		 * Write a line of values with the current timestamp every 10 msecs.
		 */
		void run();
};
