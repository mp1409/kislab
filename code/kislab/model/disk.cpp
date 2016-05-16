/**
 * @file
 *
 * The implmentation file of the Disk class.
 */

#include "disk.h"

// TODO: als parameter vllt drehrichtung?
Disk::Disk(PhotoSensor* ps, HallSensor* hs) { 
	release = new Release();
	pSensor = ps;
	hSensor = hs;
}

Disk::~Disk() {
	delete release; 
	delete pSensor;
	delete hSensor;
}

/*
* Method to let the disk run and the ball fall
*/
void Disk::go() {
	// sensoren auswerten und logs printen die in diagramme gepackt werden können
	if(pSensor->read() == 1 and hSensor->read() == 1) {
		release->open();
	}
	/* TODO:
	*  - geschwindikeit messen
	*  - anständige logik für wann fallen lassen implementieren
	*/
}
