/*
 * ZeduinoTest.cpp
 *
 * Created: 02/10/2018 19:17:02
 * Author : hugo_
 */ 

#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Sonar *sonar;
component::Display7 *display;

void setup() {
	util::prescaler(util::PS1);
	port::mode(P0, OUTPUT);
	port::mode(P1, OUTPUT);
	port::mode(P2, OUTPUT);
	port::mode(P3, OUTPUT);
	port::mode(P4, OUTPUT);
	port::mode(P5, OUTPUT);
	port::mode(P8, OUTPUT);
	port::mode(P9, OUTPUT);
	sonar = new component::Sonar(P7, P6);
	display = new component::Display7(P0, P1, P2, P3, P4, P5, P8, P9);
}

void loop() {
	uint16 distance = sonar->ReadDistance();
	display->SetValue(distance);
	display->SetDotVisibility(!display->IsDotVisible());
	util::delay_ms(500);
}

