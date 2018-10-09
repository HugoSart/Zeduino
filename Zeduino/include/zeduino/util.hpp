/*
 * Util.h
 *
 * Created: 02/10/2018 22:07:18
 *  Author: hugo_
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define tst_bit(reg,bitx) (reg&(1<<bitx))   
#define set_bit(reg,bitx) (reg|=(1<<bitx))  
#define clr_bit(reg,bitx) (reg&=~(1<<bitx))

#define fcrio(port) (port < 8 ? DDRD : DDRB)
#define fcrof(port) (port < 8 ? PORTD : PORTB)
#define fcrin(port) (port < 8 ? PIND : PINB)
#define nmr(port) (port % 8)

typedef unsigned char byte;
typedef int8_t int8;
typedef int16_t int16;
typedef uint8_t uint8;
typedef uint16_t uint16;

void * operator new(size_t size) {
	return malloc(size);	
}

void operator delete(void *ptr) {
	free(ptr);
}

namespace zeduino {
	
	namespace util {
		
		enum EPrescaler {
			PS0 = CS00, PS1 = CS01, PS2 = CS02
		};
		
		void prescaler(EPrescaler p) {
			set_bit(TCCR1B, p);
		}
		
		void delay_ms(uint16 time) {
			// TODO: Implementar em assembly
			while (time > 0) {
				_delay_ms(1);
				time--;
			}
		}
		
		void delay_us(uint16 time) {
			// TODO: Implementar em assembly
			while (time > 0) {
				_delay_us(1);
				time--;
			}
		}
		
	}
	
}

#endif /* UTIL_H_ */