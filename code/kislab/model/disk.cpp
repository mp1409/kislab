/**
 * @file
 *
 * The implmentation file of the Disk class.
 */

#include "disk.h"

// TODO: als parameter vllt drehrichtung?
Disk::Disk(PhotoSensor* ps, HallSensor* hs, Release* r) {
	_release = r;
	_pSensor = ps;
	_hSensor = hs;
}

void Disk::go() {
	/**
	 * \todo geschwindikeit messen
	 * \todo anständige logik für wann fallen lassen implementieren
	 * \todo sensoren auswerten und logs printen die in diagramme gepackt
	 * werden können
	 */
	if(_pSensor->read() == 1 and _hSensor->read() == 1) {
		_release->open();
	}
}
