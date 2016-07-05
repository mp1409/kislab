/**
 * @file
 *
 * The implementation file of the Disk class.
 */

#include "disk.h"
#include "limits.h"

bool Disk::isStable() {
	/**
	 * \todo Finish implementation!
	 */

	if(_position.value == Sensor::Value::INVALID) {
		return false;
	}

	if(_pSensorLastValue == Sensor::Value::INVALID) {
		return false;
	}

	for(unsigned short i = 0; i < _pSensorSampleSize; i++) {
		if(_pSensorLastTimes[i] == 0) {
			return false;
		}
	}

	/**
	 * \warning The following limits are reciproces of the disk speed/frequency,
	 * i.e.:
	 * \li millisPerRotLowerLimit is the \b upper limit for the speed of the
	 * disk.
	 * \li millisPerRotUpperLimit is the \b lower limit for the speed of the
	 * disk.
	 */
	const unsigned long millisPerRotLowerLimit = 1;
	const unsigned long millisPerRotUpperLimit = ULONG_MAX;
	/**
	 * \todo \b Set sensible (and tested) values for lower and upper limit.
	 */

	unsigned long currentMillisPerRot = millisPerRot();
	if((currentMillisPerRot < millisPerRotLowerLimit)
			or (currentMillisPerRot > millisPerRotUpperLimit)) {
		return false;
	}

	/**
	 * \todo Test on jumps in disk speed? Perhaps do this by checking if the
	 * previous prediction was only xy% different from the real value?
	 */

	return true;
}

void Disk::update() {
	if(_pSensorLastValue == Sensor::Value::INVALID) {
		_pSensorLastTimes[_timeIndex] = millis();
		_pSensorLastValue = _pSensor->read();
	} else if (_pSensorLastValue != _pSensor->read()) {
		_timeIndex = (_timeIndex + 1) % _pSensorSampleSize;
		if (_invalidMeasuresCount == 0) {
			_pSensorLastTimes[_timeIndex] = millis();
		} else {
			_pSensorLastTimes[_timeIndex] = 0;
			_invalidMeasuresCount--;
		}
		_pSensorLastValue = static_cast<Sensor::Value>(1 - _pSensorLastValue);
	}

	if(_position.value == Sensor::Value::INVALID) {
		_position.time = millis();
		_position.value = _hSensor->read();
	} else if(_position.value != _hSensor->read()) {
		_position.time = millis();
		_position.value = static_cast<Sensor::Value>(1 - _position.value);
	}
}

unsigned long Disk::millisPerRot() {
	unsigned long timeDiff = _pSensorLastTimes[_timeIndex]
			- _pSensorLastTimes[(_timeIndex + 1) % _pSensorSampleSize];
	double rot = static_cast<double>(_pSensorSampleSize) / 12.0;
	return timeDiff / rot;
}
