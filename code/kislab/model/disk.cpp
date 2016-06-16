/**
 * @file
 *
 * The implementation file of the Disk class.
 */

#include "disk.h"

void Disk::update() {
	if(_pSensorLastValue == -1) {
		_pSensorLastValue = _pSensor->read();
	} else if (_pSensorLastValue != _pSensor->read()) {
		_timeIndex = (_timeIndex + 1) % _pSensorSampleSize;
		_pSensorLastTimes[_timeIndex] = millis();
		_pSensorLastValue = 1 - _pSensorLastValue;
	}

	if(_position.value == -1) {
		_position.value = _hSensor->read();
	} else if(_position.value != _hSensor->read()) {
		_position.time = millis();
		_position.value = 1 - _position.value;
	}
}

double Disk::millisPerRot() {
	unsigned long timeDiff = _pSensorLastTimes[_timeIndex]
			- _pSensorLastTimes[(_timeIndex + 1) % _pSensorSampleSize];
	double rot = static_cast<double>(_pSensorSampleSize) / 12.0;
	return static_cast<double>(timeDiff) / rot;
}
