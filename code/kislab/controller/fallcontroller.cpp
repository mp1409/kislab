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
	 * result must be greate than current time + safeguard
	 */

	return 0;
}

void FallController::run() {
	/**
	 * \todo \b Implement!
	 */

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
				// releaseTheKraken
				break;
			}
		}
	}
}

void FallController::debug() {
	Serial.begin(115200);
	
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