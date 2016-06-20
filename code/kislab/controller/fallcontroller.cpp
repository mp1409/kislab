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
			delay(_defaultPollInterval);
		}

		while(_trigger->read() != Sensor::Value::ONE) {
			_disk->update();
			delay(_defaultPollInterval);
		}

		while (true) {
			_disk->update();

			if (not _disk->isStable()) {
				delay(_defaultPollInterval);
				continue;
			}

			unsigned long nextReleaseTime = calculateNextReleaseTime();
			unsigned long currentTime = millis();

			if(currentTime >= nextReleaseTime - 0.5 * _defaultPollInterval and currentTime  <= nextReleaseTime + 0.5 * _defaultPollInterval) {
				releaseTheKraken();
				break;
			}
		}
	}
}

void FallController::debug() {
	while (true) {
		_disk->update();
		Disk::DiskPosition p = _disk->position();
		Serial.print(p.value);
		Serial.print("\t");
		Serial.print(_disk->millisPerRot());
		Serial.print("\t");
		Serial.println(p.time);

	}
}

void FallController::releaseTheKraken() {
	_rel->open();
	unsigned long atm = millis() + 100;
	while(millis() < atm) {
		_disk->update();
		delay(_defaultPollInterval);
	}
	_rel->close();
}
