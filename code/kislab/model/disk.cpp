/**
 * @file
 *
 * The implementation file of the Disk class.
 */

#include "disk.h"

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

	// how long one black white switch takes in millis
	while (_pSensor->read() == 1) {}
	unsigned long start = millis();
	while (_pSensor->read() == 0) {}
	unsigned long end = millis();
	unsigned long elapsed = end - start;
}
