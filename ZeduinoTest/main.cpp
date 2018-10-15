#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER // This tells the compiler that you gonna use the setup and loop function, 
                         // otherwise you gonna need create your own main and main loop

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Sonar *sonar;

void setup() {
	port::mode(P6, INPUT);
	port::mode(P7, OUTPUT);
	sonar = new component::Sonar(P7, P6);
}

void loop() {
	debug::log("distancia: " + sonar->ReadDistance());
}

