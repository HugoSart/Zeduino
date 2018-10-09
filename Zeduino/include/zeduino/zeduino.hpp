/*
* Zeduino.h
*
* Created: 02/10/2018 22:05:03
*  Author: hugo_
*/


#ifndef ZEDUINO_H_
#define ZEDUINO_H_

#include <avr/interrupt.h>
#include "util.hpp"
#include "port.hpp"
#include "component.hpp"

namespace zeduino {}

#ifdef ZEDUINO_LAUNCHER
#pragma message("Using Zeduino Launcher template.")

void setup();
void loop();

extern "C" {
	int main() {
		setup();
		while (true) loop();
		return 0;
	}
}

#endif


#endif /* ZEDUINO_H_ */