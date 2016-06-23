/**
 * @file
 *
 * The implementation file of the ManualRelease class.
 */

#include "manualrelease.h"

void ManualRelease::run() {
	while(true) {
		while(_trigger->read() != Sensor::Value::ZERO) {
			delay(_pollInterval);
		}

		while(_trigger->read() != Sensor::Value::ONE) {
			delay(_pollInterval);
		}

		releaseTheKraken();
	}
}

void ManualRelease::releaseTheKraken() {
	_release->open();
	delay(200);
	_release->close();
}
