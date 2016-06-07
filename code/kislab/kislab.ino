/**
 * @file
 *
 * Main file of the programm, containing setup and loop functions.
 */

#include "hardware/hallsensor.h"
#include "hardware/photosensor.h"
#include "hardware/release.h"
#include "model/disk.h"
#include "utils/datawriter.h"

/**
 * Pointer to the hall sensor instance.
 */
HallSensor* hs;

/**
 * Pointer to the photo sensor instance.
 */
PhotoSensor* ps;

/**
 * The number of sensors.
 */
const unsigned int numSensors = 2;

/**
 * Array with pointers to all sensor instances (in the order they shall
 * appear in the output.
 */
Sensor* sensors[numSensors];

/**
 * Pointer to the datawriter instance.
 */
DataWriter* dw;

/**
 * Pointer to the release instance.
 */
Release* rel;

/**
 * Pointer to the disk instance.
 */
Disk* disk;

/**
 * The possible operation modes for the program.
 */
enum OperationMode {
	data_output /*!< Write sensor values to serial port. */
};

/**
 * The current mode of operation.
 */
const OperationMode mode = data_output;

/**
 * The setup function, invoked once when the Arduino is powered on or the reset
 * button was pressed.
 *
 * The classes instances should be created here (only pass away pointers).
 * Additionally, the serial setup should happen here.
 */
void setup() {
	hs = new HallSensor();
	sensors[0] = hs;

	ps = new PhotoSensor();
	sensors[1] = ps;

	rel = new Release();
	disk = new Disk(ps, hs, rel);

	if (mode == data_output) {
		Serial.begin(115200);
		dw = new DataWriter(sensors, numSensors);
	}
}

/**
 * The main loop function, run continiously.
 */
void loop() {
	if (mode == data_output) {
		dw->writeValues();
		delay(10);
	}
}
