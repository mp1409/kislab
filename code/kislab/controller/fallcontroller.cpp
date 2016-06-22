/**
 * @file
 *
 * The implementation file of the FallController class.
 */

#include "fallcontroller.h"

unsigned long FallController::calculateNextReleaseTime() {
	/**
	 * \todo \b Implement!
	 *
	 * Add approximation function
	 */

	Disk::DiskPosition diskPos = _disk->position();
	unsigned long inPositionTime = diskPos.time;

	if(diskPos.value == Sensor::Value::ONE) {
		inPositionTime += _disk->millisPerRot() / 2;
		// TODO make millisPerRot unsigned long
	} else if (diskPos.value == Sensor::Value::ZERO) {
		inPositionTime += _disk->millisPerRot();
	} else {
		/**
		 * \todo \b Implement!
		 *
		 * Fail, sensor invalid. This should not happen on a stable disk.
		 */
		return 0;
	}

	const unsigned long fallTime = static_cast<unsigned long>(
			sqrt(2 * 0.75 / 9.81) * 1000
	);

	return inPositionTime - fallTime - 35;
	//return millis() + 5;
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
	unsigned long timeToClose = millis() + 200;
	while(millis() < timeToClose) {
		_disk->update();
		delay(_pollInterval);
	}
	_release->close();
}
