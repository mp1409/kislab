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

Sensor* sensors[2];

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
 * The setup function, invoked once when the Arduino is powered on or the reset
 * button was pressed.
 *
 * The classes instances should be created here (only pass away pointers).
 * Additionally, the serial setup should happen here.
 */
void setup() {
	hs = new HallSensor();
	ps = new PhotoSensor();
	rel = new Release();
	disk = new Disk(ps, hs, rel);

	sensors[0] = hs;
	sensors[1] = ps;

	Serial.begin(115200);

	dw = new DataWriter(sensors, 2);
}

/**
 * The main loop function, run continiously.
 */
void loop() {
	dw->writeValues();
	delay(10);
}
