#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER
#define ZEDUINO_AUTO

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Led *led;
component::Button *button;

void setup() {
	led = new component::Led(P8);
	button = new component::Button(P9);
	led->TurnOff();
}

void loop() {
	led->TurnOn(button->IsPressed());
}

