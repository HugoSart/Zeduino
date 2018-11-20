#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER
#define ZEDUINO_AUTO

#include <util/delay.h>
#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Led *led;
component::Sonar *sonar;

void setup() {
	led = new component::Led(P13);
	sonar = new component::Sonar(P2, P3);
}

void loop() {
	led->Blink(sonar->ReadDistance() * 100);
}

