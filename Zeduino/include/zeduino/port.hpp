/*
* Port.h
*
* Created: 02/10/2018 22:04:38
*  Author: hugo_
*/


#ifndef PORT_H_
#define PORT_H_

#include "util.hpp"

namespace zeduino {
	
	namespace port {
		
		enum EMode {
			INPUT, OUTPUT
		};
		
		enum EPort {
			P0, P1, P2, P3, P4, P5, P6, P7, // DDRD
			P8, P9, P10, P11, P12, P13 // DDRB
		};
		
		void mode(EPort port, EMode m) {
			if (m == INPUT) _CLEAR_BIT(fcrio(port), nmr(port));
			else if (m == OUTPUT) _SET_BIT(fcrio(port), nmr(port));
		}
		
		inline EMode get_mode(EPort port) {
			return (EMode)_GET_BIT(fcrio(port), nmr(port));
		}
		
		inline void enable(EPort port) {
			_SET_BIT(fcrof(port), nmr(port));
		}
		
		inline void enable(EPort port, bool b) {
			if (b) _SET_BIT(fcrof(port), nmr(port));
			else _CLEAR_BIT(fcrof(port), nmr(port));
		}
		
		inline void disable(EPort port) {
			_CLEAR_BIT(fcrof(port), nmr(port));
		}
		
		inline bool is_enabled(EPort port) {
			return _GET_BIT(fcrof(port), nmr(port));
		}
		
		inline bool read(EPort port) {
			return _GET_BIT(fcrin(port), nmr(port));
		}
		
		inline void toggle(EPort port) {
			if (is_enabled(port)) disable(port);
			else enable(port);
		}
		
	}
	
}



#endif /* PORT_H_ */