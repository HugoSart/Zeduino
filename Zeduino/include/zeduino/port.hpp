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
		
		enum EState {
			ENABLED, DISABLED
		};
		
		void mode(EPort port, EMode m) {
			if (m == INPUT) clr_bit(fcrio(port), nmr(port));
			else if (m == OUTPUT) set_bit(fcrio(port), nmr(port));
		}
		
		inline EMode get_mode(EPort port) {
			return (EMode)tst_bit(fcrio(port), nmr(port));
		}
		
		inline void enable(EPort port) {
			set_bit(fcrof(port), nmr(port));
		}
		
		inline void enable(EPort port, bool b) {
			if (b) set_bit(fcrof(port), nmr(port));
			else clr_bit(fcrof(port), nmr(port));
		}
		
		inline void disable(EPort port) {
			clr_bit(fcrof(port), nmr(port));
		}
		
		inline bool is_enabled(EPort port) {
			return tst_bit(fcrof(port), nmr(port));
		}
		
		inline uint16 read(EPort port) {
			return tst_bit(fcrin(port), nmr(port));
		}
		
		inline void toggle(EPort port) {
			if (is_enabled(port)) disable(port);
			else enable(port);
		}
		
	}
	
}



#endif /* PORT_H_ */