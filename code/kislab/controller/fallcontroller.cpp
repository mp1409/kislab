/**
 * @file
 *
 * The implementation file of the FallController class.
 */

#include "fallcontroller.h"

unsigned long FallController::calculateNextReleaseTime() {
	unsigned long millisPerRot = _disk->millisPerRot();
	double a = 0.0;
	if (millisPerRot != 0) {
		// h^-1(t)
		double t = 212.162 - (0.27027 * sqrt(56933.0 pow((double) millisPerRot, 2.0) + 2.22e8 * (double) millisPerRot)) / (double) millisPerRot;	
		// h'(t) - acceleration of timePerRot
		a = (6.88093e9 - 3.24324e7 * t) / pow(pow(t, 2) - 424.324 * t + 40854.1, 2);
	}

	Disk::DiskPosition diskPos = _disk->position();
	unsigned long inPositionTime = diskPos.time;

	if(diskPos.value == Sensor::Value::ONE) {
		inPositionTime += millisPerRot / 2 + (unsigned long) a / 2;
	} else  {
		/**
		 * diskPos.value == Sensor::Value::ZERO. Sensor::Value::INVALID not
		 * possible because disk is stable.
		 */
		inPositionTime += millisPerRot + (unsigned long) a;
	}

	const unsigned long fallTime = static_cast<unsigned long>(
			sqrt(2 * 0.75 / 9.81) * 1000
	);

	return inPositionTime - fallTime - 35;
}

void FallController::update() {
	_disk->update();

	Sensor::Value currentTriggerState = _trigger->read();
	unsigned long currentTime = millis();

	if(_lastTriggerState == Sensor::Value::INVALID) {
		_lastTriggerState = currentTriggerState;
		_lastTriggerTime = currentTime;
	} else if(currentTime - _lastTriggerTime > _triggerCooldown) {
		if((_lastTriggerState == Sensor::Value::ZERO) and
				(currentTriggerState == Sensor::Value::ONE)) {
			_triggerCount++;
		}

		_lastTriggerState = currentTriggerState;
		_lastTriggerTime = currentTime;
	}
}

void FallController::run() {
	while(true) {
		update();
		delay(_pollInterval);

		while (_triggerCount > 0) {
			update();

			if (not _disk->isStable()) {
				delay(_pollInterval);
				continue;
			}

			unsigned long nextReleaseTime = calculateNextReleaseTime();
			unsigned long currentTime = millis();


			if(currentTime >= nextReleaseTime - 0.5 * _pollInterval and
					currentTime  <= nextReleaseTime + 0.5 * _pollInterval) {
				releaseTheKraken();
			}

			delay(_pollInterval);
		}

	}
}

void FallController::releaseTheKraken() {
	_release->open();
	unsigned long timeToClose = millis() + 200;
	while(millis() < timeToClose) {
		update();
		delay(_pollInterval);
	}
	_release->close();

	_disk->invalidate();

	_triggerCount--;
}
