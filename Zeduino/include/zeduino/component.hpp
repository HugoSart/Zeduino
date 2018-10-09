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

using namespace zeduino::port;

namespace zeduino {
	
	namespace component {
		
		class Component {};
		
		class Led : public Component {
			
			private: const EPort _port;
			
			public: Led(EPort port) : _port(port) {}
			
			public: inline bool IsOn() { return is_enabled(_port); }
			public: inline void TurnOn() { enable(_port); }
			public: inline void TurnOff() { disable(_port);	}
			public: inline void Toggle() { if (is_enabled(_port)) disable(_port); else enable(_port); }
			
			public: inline void Blink(const uint8_t time) {
				Toggle();
				util::delay_ms(time);
			}
			
		};
		
		class Display7 : public Component {
			
			private: EPort _port[8];
			
			public: Display7(EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h) {
				_port[0] = a; _port[1] = b; _port[2] = c; _port[3] = d; _port[4] = e; _port[5] = f; _port[6] = g; _port[7] = h;
			}
			
			public: void SetDotVisibility(bool b) { enable(_port[7], b); }
			public: bool IsDotVisible() { return is_enabled(_port[7]); }
			
			public: void SetValue(uint8 hex) {
				if (hex > 15) hex = 15;
				else if (hex < 0) hex = 0;
				
				if (hex == 0x0) {
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					disable(_port[6]);
				} else if (hex == 0x1) {
					disable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					disable(_port[3]);
					disable(_port[4]);
					disable(_port[5]);
					disable(_port[6]);
				} else if (hex == 0x2) {
					enable(_port[0]);
					enable(_port[1]);
					disable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					disable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x3) {
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					disable(_port[4]);
					disable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x4) {
					disable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					disable(_port[3]);
					disable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x5) {
					enable(_port[0]);
					disable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					disable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x6) {
					enable(_port[0]);
					disable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x7) {
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					disable(_port[3]);
					disable(_port[4]);
					disable(_port[5]);
					disable(_port[6]);
				} else if (hex == 0x8) {
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0x9) {
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					disable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0xA) { // A
					enable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					disable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0xB) { 
					disable(_port[0]);
					disable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0xC) { 
					enable(_port[0]);
					disable(_port[1]);
					disable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					disable(_port[6]);
				} else if (hex == 0xD) { 
					disable(_port[0]);
					enable(_port[1]);
					enable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					disable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0xE) {
					enable(_port[0]);
					disable(_port[1]);
					disable(_port[2]);
					enable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				} else if (hex == 0xF) {
					enable(_port[0]);
					disable(_port[1]);
					disable(_port[2]);
					disable(_port[3]);
					enable(_port[4]);
					enable(_port[5]);
					enable(_port[6]);
				}
				
			}
				
				
		};
		
		class Sonar : public Component {
		
			private: const EPort _triggerPort, _echoPort;
			private: uint16 count;
			
			public: Sonar(EPort triggerPort, EPort echoPort) : _triggerPort(triggerPort), _echoPort(echoPort) {}
				
			public: uint16 ReadDistance() {
				
				port::enable(_triggerPort);
				util::delay_us(10);
				port::disable(_triggerPort);
				
				while (!port::read(_echoPort));
				TCNT1 = 0;
				
				while (port::read(_echoPort));
				count = TCNT1;
				
				uint16 ret = (uint16)(count / 116);
				util::delay_ms(60);
				
				return ret;
				
			}
			
		};
		
	}
	
}



#endif /* COMPONENT_H_ */