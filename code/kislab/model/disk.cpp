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
		_lastTimes[_timeIndex++] = millis();
		_lastSlope = 1 - _lastSlope;
	}
}

double Disk::millisPerRot() {
	unsigned long timeDiff = _lastTimes[_timeIndex] - _lastTimes[(_timeIndex + 1) % _pSensorSampleSize];
	double rot = static_cast<double>(_pSensorSampleSize) / 12.0;
	return static_cast<double>(timeDiff) / rot;
}