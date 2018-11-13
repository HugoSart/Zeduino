/*
* Component.h
*
* Created: 03/10/2018 00:13:50
*  Author: hugo_
*/


#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <util/delay.h>
#include "util.hpp"
#include "port.hpp"
#include "debug.hpp"

using namespace zeduino::port;

namespace zeduino {
	
	namespace component {
		
		class Component {};
		
		class Led : public Component {
			
			private: const EPort _port;
			
			public: Led(EPort port) : _port(port) {
				mode(port, OUTPUT);
			}
			
			public: inline bool IsOn() { return is_enabled(_port); }
			public: inline void TurnOn() { enable(_port); }
			public: inline void TurnOn(bool b) { enable(_port, b); }
			public: inline void TurnOff() { disable(_port);	}
			public: inline void Toggle() { if (is_enabled(_port)) disable(_port); else enable(_port); }
			
			public: inline void Blink(const uint16_t time) {
				Toggle();
				util::delay_ms(time);
				Toggle();
				util::delay_ms(time);
			}
			
		};
		
		class Button : public Component {
		
			private: EPort _input;
			private: bool _alreadyPressed = false;
			private: bool _lastState = false;
		
			public: Button(EPort input) : _input(input) {
				mode(input, INPUT);
			}
			
			public: inline bool IsPressed() {
				return !port::read(_input);
			}
			
			public: bool JustPressed() {
				
				bool isPressed = IsPressed();
				
				if (isPressed && _alreadyPressed) {
					return false;
				} else if (_alreadyPressed) {
					_alreadyPressed = false;
				} else if (isPressed) { 
					_alreadyPressed = true; 
					return true; 
				}
				
				return false;
				
			}
			
			public: bool JustReleased() {
				
				if (_lastState && !IsPressed()) {
					_lastState = false;
					return true;
				}
				
				_lastState = IsPressed();
				return false;
			}
			
		};
		
		class Display7 : public Component {
			
			private: EPort _port[8];
			
			public: enum EType {
				CATHODE, ANODE	
			};
			
			public: EType type;
			
			public: Display7(EType type, EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h) : type(type) {
				_port[0] = a; _port[1] = b; _port[2] = c; _port[3] = d; _port[4] = e; _port[5] = f; _port[6] = g; _port[7] = h; 
				for (auto &p : _port)
					mode(p, OUTPUT);
			}
			
			public: Display7(EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h) : Display7(ANODE, a, b, c, d, e, f, g, h) {}
			
			public: void SetDotVisibility(bool b) { enable(_port[7], IsCathode() == true ? b : !b); }
			public: bool IsDotVisible() { return IsCathode() == true? is_enabled(_port[7]) : !is_enabled(_port[7]); }
			
			public: void SetValue(uint8 hex) {
				
				if (hex > 15) hex = 15;
				else if (hex < 0) hex = 0;
				
				if (hex == 0x0) EnablePins(true, true, true, true, true, true, false);
				else if (hex == 0x1) EnablePins(false, true, true, false, false, false, false);
				else if (hex == 0x2) EnablePins(true, true, false, true, true, false, true);
				else if (hex == 0x3) EnablePins(true, true, true, true, false, false, true);
				else if (hex == 0x4) EnablePins(false, true, true, false, false, true, true);
				else if (hex == 0x5) EnablePins(true, false, true, true, false, true, true);
				else if (hex == 0x6) EnablePins(true, false, true, true, true, true, true);
				else if (hex == 0x7) EnablePins(true, true, true, false, false, false, false);
				else if (hex == 0x8) EnablePins(true, true, true, true, true, true, true);
				else if (hex == 0x9) EnablePins(true, true, true, true, false, true, true);
				else if (hex == 0xA) EnablePins(true, true, true, false, true, true, true);
				else if (hex == 0xB) EnablePins(false, false, true, true, true, true, true);
				else if (hex == 0xC) EnablePins(true, false, false, true, true, true, false);
				else if (hex == 0xD) EnablePins(false, true, true, true, true, false, true);
				else if (hex == 0xE) EnablePins(true, false, false, true, true, true, true);
				else if (hex == 0xF) EnablePins(true, false, false, false, true, true, true);
				
			}
			
			private: inline bool IsCathode() {
				return type == CATHODE;
			}
			
			private: void EnablePins(bool a, bool b, bool c, bool d, bool e, bool f, bool g) {
				bool inv = IsCathode();
				enable(_port[0], inv == true ? a : !a);
				enable(_port[1], inv == true ? b : !b);
				enable(_port[2], inv == true ? c : !c);
				enable(_port[3], inv == true ? d : !d);
				enable(_port[4], inv == true ? e : !e);
				enable(_port[5], inv == true ? f : !f);
				enable(_port[6], inv == true ? g : !g);
			}
				
				
		};
		
		class Sonar : public Component {
		
			private: const EPort _triggerPort, _echoPort;
			private: uint16 count;
			
			public: Sonar(EPort triggerPort, EPort echoPort) : _triggerPort(triggerPort), _echoPort(echoPort) {
				mode(triggerPort, OUTPUT);
				mode(echoPort, INPUT);
			}
					
			public: uint16 ReadDistance() {
				
				port::enable(_triggerPort);
				util::delay_us(10);
				port::disable(_triggerPort);
				
				while (!port::read(_echoPort));
				TCNT1 = 0;
				
				while (port::read(_echoPort));
				count = TCNT1;
				
				uint16 ret = (uint16)(count / 116);
				printf("\ndistancia: %d\n", ret);
				util::delay_ms(60);
				
				return ret;
				
			}
			
		};
		
		class DHT11 : public Component {
			
			private: EPort _port;
			private: uint8 _cache[5] = {0};
		
			public: DHT11(EPort port) : _port(port) {
				util::delay_ms_static(1000);
			}
			
			public: int8 ReadTemperature() {
				return _cache[2];
			}
			
			public: int8 ReadHumidity() {
				return _cache[0];
			}
				
			public: void Update() {
				
				RequestUpdate();
				ClearCache();
				
				uint8 reg = 0;
				for (uint8 i = 0; i < 40; i++) {
					
					while (!read(_port));
					
					uint8 count = 0;
					while(read(_port) && count <= 35) {
						util::delay_us_static(2);
						count++;
					}
					
					if (count >= 14) {						
						_cache[reg] = util::set_bit(_cache[reg], i % 8);
						printf("_cache[%d] = %d\n", reg, _cache[reg]);
					}
					if (i % 8 == 0) reg++;
					
				}
				
			}
			
			private: inline void ClearCache() {
				for (int i = 0; i < 5; i++)
					_cache[i] = 0;
			}
			
			private: inline void RequestUpdate() {
				
				mode(_port, OUTPUT);
				enable(_port);
				disable(_port);
				util::delay_ms_static(20);
				enable(_port);
				mode(_port, INPUT);
				
				while (read(_port));
				while (!read(_port));
				while (read(_port));
				
			}
			
		};
		
		class DisplayLCD : public Component {
			
			private: enum EOperationMode {COMMAND = 0, DATA = 1};
			
			private: EPort _pMode, _pPulse, _ports[4];
			
			public: DisplayLCD(EPort mode, EPort pulse, EPort ports[]) : _pMode(mode), _pPulse(pulse) {
				for (int i = 0 ; i < 4; i++) {
					_ports[i] = ports[i];
					port::mode(_ports[i], OUTPUT);
				}
				port::mode(_pMode, OUTPUT);
				port::mode(_pPulse, OUTPUT);
				
				util::delay_ms_static(20);
				SendCommand(0x33);
				SendCommand(0x32);
				SendCommand(0x28);
				SendCommand(0x0C);
				SendCommand(0x06);
				SendCommand(0x01);
				util::delay_ms_static(2);
			}
			
				
			public: void Write(char str[]) {
				ClearScreen();
				SendCommand(0x80);
				for (int i = 0; i < 32 && str[i] != '\0'; i++) {
					if (i == 16 || str[i] == '\n') SendCommand(0xC0);
					Write(str[i]);
				}
			}
			
			public: void Write(char c) {
				SetUpperNibble(c);
				SetOperationMode(DATA);
				SetEnabled(true);
				util::delay_us_static(1);
				SetEnabled(false);
				util::delay_us_static(200);
				SetLowerNibble(c);
				SetEnabled(true);
				util::delay_us_static(1);
				SetEnabled(false);
				util::delay_ms_static(2);
			}
			
			public: void ClearScreen() {
				SendCommand(0x01);
				util::delay_ms_static(2);
				SendCommand(0x80);
			}
			
			private: void SendCommand(byte cmd) {
				SetUpperNibble(cmd);
				SetOperationMode(COMMAND);
				SetEnabled(true);
				util::delay_us_static(1);
				SetEnabled(false);
				util::delay_us_static(200);
				SetLowerNibble(cmd);
				SetEnabled(true);	
				util::delay_us_static(1);
				SetEnabled(false);
				util::delay_ms_static(2);
			}
			
			private: inline void SetOperationMode(EOperationMode m) {
				port::enable(_pMode, m);
			}
			
			private: inline void SetEnabled(bool b) {
				enable(_pPulse, b);
			}
			
			private: inline void SetUpperNibble(uint8 data) {
				enable(_ports[0], util::get_bit(data, 4));
				enable(_ports[1], util::get_bit(data, 5));
				enable(_ports[2], util::get_bit(data, 6));
				enable(_ports[3], util::get_bit(data, 7));
			}
			
			private: inline void SetLowerNibble(uint8 data) {
				enable(_ports[0], util::get_bit(data, 0));
				enable(_ports[1], util::get_bit(data, 1));
				enable(_ports[2], util::get_bit(data, 2));
				enable(_ports[3], util::get_bit(data, 3));
			}
				
		};
		
	}
	
}



#endif /* COMPONENT_H_ */