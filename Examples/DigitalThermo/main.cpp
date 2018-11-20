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
	
	char str[40] = "Temp.        0 CHumidade     0 %%";
	lcd->Write(str);
	
}

void loop() {

	component::DHT11::Response response = dht11->Read();
	
	char tempStr[5], humStr[5];
	
	if (response.checksum) {
		sprintf(tempStr, "%4d", response.temperature);
		sprintf(humStr, "%4d", response.humidity);
	} else {
		sprintf(tempStr, "ERRO");
		sprintf(humStr, "ERRO");
	}

	lcd->Write(tempStr, 0, 10);
	lcd->Write(humStr, 1, 10);
	
}