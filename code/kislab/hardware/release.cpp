/**
 * @file
 *
 * The implementation file of the Release class.
 */

#include "release.h"

Release::Release() : Component(9) {
	_servo.attach(_pin);
	close();
}
