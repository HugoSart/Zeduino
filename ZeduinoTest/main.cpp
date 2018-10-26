#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER
#define ZEDUINO_AUTO

#include <util/delay.h>
#include <zeduino/zeduino.hpp>

using namespace zeduino;

void setup() {
	//port::mode(P5, OUTPUT);
}

void loop() {
	//port::enable(P5);
	port::ctc(P6, 2000);
	//util::delay_ms(1000);
	//port::disable(P5);
	//util::delay_ms(1000);
}

