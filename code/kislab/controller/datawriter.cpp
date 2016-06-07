/**
 * @file
 *
 * The implementation file of the DataWriter class.
 */

#include "datawriter.h"

DataWriter::DataWriter(Sensor** sensors, unsigned int numSensors) :
		_sensors(sensors), _numSensors(numSensors) {
	Serial.print("Time(ms)");

	for(unsigned int i = 0; i < _numSensors; i++) {
		Serial.print(",");
		Serial.print(_sensors[i]->name());
	}

	Serial.println();
}

void DataWriter::run() {
	while (true) {
		Serial.print(millis());

		for(unsigned int i = 0; i < _numSensors; i++) {
			Serial.print(",");
			Serial.print(_sensors[i]->read());
		}

		Serial.println();

		delay(10);
	}
}
