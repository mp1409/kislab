/**
 * @file
 *
 * Main file of the programm, containing setup and loop functions.
 */

#include "controller/datawriter.h"
#include "controller/debugcontroller.h"
#include "controller/fallcontroller.h"
#include "controller/manualrelease.h"
#include "hardware/hallsensor.h"
#include "hardware/photosensor.h"
#include "hardware/release.h"
#include "model/disk.h"

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
 * Pointer to the trigger instance.
 */
Trigger* trigger;

/**
 * Pointer to the release instance.
 */
Release* rel;

/**
 * Pointer to the disk instance.
 */
Disk* disk;

/**
 * Pointer to the controller instance.
 */
Controller* controller;

/**
 * The setup function, invoked once when the Arduino is powered on or the reset
 * button was pressed.
 *
 * The classes instances should be created here (only pass away pointers).
 * Additionally, the serial setup should happen here.
 */
void setup() {
	Serial.begin(115200);

	hs = new HallSensor();
	sensors[0] = hs;

	ps = new PhotoSensor();
	sensors[1] = ps;

	trigger = new Trigger();

	rel = new Release();

	disk = new Disk(ps, hs);

	// controller = new DataWriter(sensors, numSensors);
	controller = new FallController(disk, rel, trigger);
	// controller = new DebugController(disk);
	// controller = new ManualRelease(rel, trigger);
}

/**
 * The main loop function. By the Arduino platform, it is run continiously.
 * However, we ignore this, and implement our own endless loop in the run method
 * of the Controllers, because this better suits object-oriented design.
 */
void loop() {
	controller->run();
}
