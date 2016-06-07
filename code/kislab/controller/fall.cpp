/**
 * @file
 *
 * The implementation file of the Fall class.
 */

#include "fall.h"

int Fall::calculateNextReleaseTime() {
	/**
	 * \todo \b Implement!
	 * use pos and speed from disk to determine in_position_time
	 * subtract fall time (including servo reaction time etc)
	 * result must be greate than current time + safeguard
	 */

	return 0;
}

void Fall::run() {
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
