/**
 * @file
 *
 * Main file of the programm, containing setup and loop functions.
 */

#include "model/disk.h"
#include "hardware/hallsensor.h"
#include "hardware/photosensor.h"
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
 * Pointer to the datawriter instance.
 */
DataWriter* dw;

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

	Serial.begin(115200);

	Sensor* sensors[] = { hs, ps };
	dw = new DataWriter(sensors, 2);

}

/**
 * The main loop function, run continiously.
 */
void loop() {
	dw->writeValues();
	delay(10);
}
