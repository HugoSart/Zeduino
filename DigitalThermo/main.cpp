/*
 * DigitalThermo.cpp
 *
 * Created: 07/11/2018 09:40:41
 * Author : hugo_
 */ 

#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::DisplayLCD *lcd;
component::DHT11 *dht11;

void setup() {
	EPort ports[] = {P5, P4, P3, P2};
	lcd = new component::DisplayLCD(P12, P11, ports);
	lcd->Write("Zeduino    DHT11Iniciando  ");
	
	for (int i = 0; i < 2; i++) {
		lcd->Write('.');
		util::delay_ms(500);
	}
	
	dht11 = new component::DHT11(P13);
	
	for (int i = 0; i < 3; i++) {
		lcd->Write('.');
		util::delay_ms(500);
	}
}

void loop() {
	
	static int8 temp = 0, hum = 0;
	dht11->Update();
	temp = dht11->ReadTemperature();
	hum = dht11->ReadHumidity();
	
	printf("\n%2d, %2d\n\n", temp, hum);
	
	char str[32];
	sprintf(str, "Temp.     %4d CHumidade  %4d %%", temp, hum);
	lcd->Write(str);
	
}