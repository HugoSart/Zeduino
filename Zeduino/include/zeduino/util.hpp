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
		
		inline void delay_ms(uint16 time) {
			while (time > 0) {
				asm volatile(
					"    ldi  r18, 21"	"\n"
					"    ldi  r19, 199"	"\n"
					"1:  dec  r19"		"\n"
					"    brne 1b"		"\n"
					"    dec  r18"		"\n"
					"    brne 1b"		"\n"
				);
				time--;
			}
		}
		
		inline void delay_us(uint16 time) {
			while (time > 0) {
				asm volatile(
					"    ldi  r18, 5"	"\n"
					"1:  dec  r18"		"\n"
					"    brne 1b"		"\n"
					"    nop"			"\n"
				);
				time--;
			}
		}
		
	}
	
}

#endif /* UTIL_H_ */