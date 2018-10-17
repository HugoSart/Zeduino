/*
* zeduino.hpp
*
* Created: 02/10/2018 22:05:03
*  Author: hugo_
*/


#ifndef ZEDUINO_H_
#define ZEDUINO_H_

#include <avr/io.h>
#include "util.hpp"
#include "port.hpp"
#include "component.hpp"
#include "util.hpp"
#include "clock.hpp"

namespace zeduino {}

#ifdef ZEDUINO_AUTO
#pragma message("Using Zeduino auto port configuration.")
#endif

#ifdef ZEDUINO_LAUNCHER
#pragma message("Using Zeduino Launcher template.")

void setup();
void loop();

extern "C" {
	int main() {
		
		DDRB  = 0b00000000;
		DDRD  = 0b00000000;
		PORTB = 0b11111111;
		PORTD = 0b11111111;
		
		uart_init();
		zeduino::clock::prescaler(zeduino::clock::PS1);
		setup();
		while (true) loop();
		return 0;
	}
}

#endif


#endif /* ZEDUINO_H_ */