/**
 * @file
 *
 * The implementation file of the FallController class.
 */

#include "fallcontroller.h"

unsigned long FallController::calculateNextReleaseTime() {
	/**
	 * \todo \b Implement!
	 * use pos and speed from disk to determine in_position_time
	 * subtract fall time (including servo reaction time etc)
	 *
	 * result must be greate than current time + safeguard (<- do we need this?
	 * especially safeguard? nrt can only be one or two millis in the future...)
	 */

	return millis() + 5;
}

void FallController::run() {
	while(true) {
		while(_trigger->read() != Sensor::Value::ZERO) {
			_disk->update();
			delay(_pollInterval);
		}

		while(_trigger->read() != Sensor::Value::ONE) {
			_disk->update();
			delay(_pollInterval);
		}

		while (true) {
			_disk->update();

			if (not _disk->isStable()) {
				delay(_pollInterval);
				continue;
			}

			unsigned long nextReleaseTime = calculateNextReleaseTime();
			unsigned long currentTime = millis();

			if(currentTime >= nextReleaseTime - 0.5 * _pollInterval and
					currentTime  <= nextReleaseTime + 0.5 * _pollInterval) {
				releaseTheKraken();
				break;
			}
		}
	}
}

void FallController::releaseTheKraken() {
	_release->open();
	unsigned long timeToClose = millis() + 100;
	while(millis() < timeToClose) {
		_disk->update();
		delay(_pollInterval);
	}
	_release->close();
}
