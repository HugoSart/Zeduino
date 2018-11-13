/*
 * clock.h
 *
 * Created: 16/10/2018 01:22:51
 *  Author: hugo_
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_

#include <avr/io.h>

namespace zeduino {
	
	namespace clock {
		
		enum EPrescaler {
			PS0 = CS00, PS1 = CS01, PS2 = CS02
		};
		
		inline void prescaler(EPrescaler p) {
			_SET_BIT(TCCR1B, p);
		}
		
	}
	
}


#endif /* CLOCK_H_ */