/**
 * @file
 *
 * The implementation file of the Disk class.
 */

#include "disk.h"

void Disk::update() {
	Serial.print("update method called\t"); // DEBUG
	Serial.println(_pSensor->read()); // DEBUG

	if(_pSensorLastValue == Sensor::Value::INVALID) {
		Serial.println("update after invalid\t"); // DEBUG
		_pSensorLastTimes[_timeIndex] = millis();
		_pSensorLastValue = _pSensor->read();
	} else if (_pSensorLastValue != _pSensor->read()) {



		_timeIndex = (_timeIndex + 1) % _pSensorSampleSize;
		_pSensorLastTimes[_timeIndex] = millis();
		_pSensorLastValue = static_cast<Sensor::Value>(1 - _pSensorLastValue);

		Serial.print("update\t"); // DEBUG
		Serial.print(_timeIndex); // DEBUG
		Serial.print("\t"); // DEBUG
		Serial.print(millis()); // DEBUG
		Serial.print("\t"); // DEBUG
		Serial.println(_pSensorLastValue); // DEBUG
	}

	if(_position.value == Sensor::Value::INVALID) {
		_position.time = millis();
		_position.value = _hSensor->read();
	} else if(_position.value != _hSensor->read()) {
		_position.time = millis();
		_position.value = static_cast<Sensor::Value>(1 - _position.value);
	}
}

double Disk::millisPerRot() {
	/*Serial.print("sensorLastTimes\t"); // DEBUG
	Serial.print(_pSensorLastTimes[(_timeIndex + 1) % _pSensorSampleSize]); // DEBUG
	Serial.print("\t"); // DEBUG
	Serial.println(_pSensorLastTimes[_timeIndex]); // DEBUG
	*/
	unsigned long timeDiff = _pSensorLastTimes[_timeIndex]
			- _pSensorLastTimes[(_timeIndex + 1) % _pSensorSampleSize];
	double rot = static_cast<double>(_pSensorSampleSize) / 12.0;
	return static_cast<double>(timeDiff) / rot;
}
