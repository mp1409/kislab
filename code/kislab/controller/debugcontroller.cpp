/**
 * @file
 *
 * The implementation file of the DebugController class.
 */

#include "debugcontroller.h"

void DebugController::run() {
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
