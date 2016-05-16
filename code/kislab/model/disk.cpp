/**
 * @file
 *
 * The implmentation file of the Disk class.
 */

#include "disk.h"

// TODO: als parameter vllt drehrichtung?
Disk::Disk() { 
	release = new Release();
	pSensor = new PhotoSensor();
	hSensor = new HallSensor();
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
}
