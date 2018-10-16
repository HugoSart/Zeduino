#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER // This tells the compiler that you gonna use the setup and loop function, 
                         // otherwise you gonna need create your own main and main loop

#include <zeduino/zeduino.hpp>

using namespace zeduino;

#define TRIGGER P2
#define ECHO P3
#define LED P13

component::Sonar *sonar;
component::Led *led;

void setup() {
	
	port::mode(TRIGGER, OUTPUT);
	port::mode(LED, OUTPUT);
	
	sonar = new component::Sonar(TRIGGER, ECHO);
	led = new component::Led(LED);
	
	led->TurnOn();
	
}

void loop() {
	uint16 distance = sonar->ReadDistance();
	led->Blink(distance * 10);
}

