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
			
			public: inline void Blink(const uint16_t time) {
				Toggle();
				util::delay_ms(time);
			}
			
		};
		
		/*class Button : public Component {
		
			public: enum EAction {
				PRESSED, RELEASED
			}
			
			public: enum EDetection {
				ONE, CONTINUOUSLY	
			};
		
			private: const EPort _pullUp, _pressed;
			private: const EAction _action;
			private: const EDetection _detection;
		
			public: Button(EAction action, EDetection detection, EPort pullUp, EPort pressed) : action(_action), detection(_detection), pullUp(_pullUp), pressed(_pressed) {}
				
			public: bool IsPressed() {
				return port::read(_pressed);
			}
			
		};*/
		
		class Display7 : public Component {
			
			private: EPort _port[8];
			
			public: enum EType {
				CATHODE, ANODE	
			};
			
			public: EType type;
			
			public: Display7(EType type, EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h) : type(type) {
				_port[0] = a; _port[1] = b; _port[2] = c; _port[3] = d; _port[4] = e; _port[5] = f; _port[6] = g; _port[7] = h; 
			}
			
			public: Display7(EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h) : Display7(CATHODE, a, b, c, d, e, f, g, h) {}
			
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