/**
 * @file
 *
 * The implementation file of the Disk class.
 */

#include "disk.h"

/*
	// how long one black white switch takes in millis
	while (_pSensor->read() == 1) {}
	unsigned long start = millis();
	while (_pSensor->read() == 0) {}
	unsigned long end = millis();
	unsigned long elapsed = end - start;
*/

void Disk::update() {
	if(_lastSlope == -1) {
		_lastSlope = _pSensor->read();
	} else if (_lastSlope != _pSensor->read()) {
		_timeIndex = (_timeIndex + 1) % _pSensorSampleSize;
		_pSensorLastTimes[_timeIndex] = millis();
		_lastSlope = 1 - _lastSlope;
	}

	if(_hSensorPosition.position == -1) {
		_hSensorPosition.position = _hSensor->read();
	} else if(_hSensorPosition.position != _hSensor->read()) {
		_hSensorPosition.lastTime = millis();
		_hSensorPosition.position = 1 - _hSensorPosition.position;
	}
}

double Disk::millisPerRot() {
	unsigned long timeDiff = _pSensorLastTimes[_timeIndex] - _pSensorLastTimes[(_timeIndex + 1) % _pSensorSampleSize];
	double rot = static_cast<double>(_pSensorSampleSize) / 12.0;
	return static_cast<double>(timeDiff) / rot;
}