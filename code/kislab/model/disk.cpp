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
}
