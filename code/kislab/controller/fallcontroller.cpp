/**
 * @file
 *
 * The implementation file of the FallController class.
 */

#include "fallcontroller.h"

//int FallController::calculateNextReleaseTime() {
	/**
	 * \todo \b Implement!
	 * use pos and speed from disk to determine in_position_time
	 * subtract fall time (including servo reaction time etc)
	 * result must be greate than current time + safeguard
	 */

//	return 0;
//}

void FallController::run() {
	/**
	 * \todo \b Implement!
	 */

	while (true) {
		/** \todo
		 *
		 * Wait until trigger has been pressed.
		 *
		 * if stable
		 *		calculate next release time (=nrt)
		 *		if time in [nrt - 0,5 * polldelay, nrt + 0,5 * polldelay) # compiler pragma unlikely
		 *			releaseTheKraken
		 *	short delay
		 */
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