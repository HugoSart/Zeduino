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

#define _GET_BIT(reg,bitx) (reg&(1<<bitx))   
#define _SET_BIT(reg,bitx) (reg|=(1<<bitx))  
#define _CLEAR_BIT(reg,bitx) (reg&=~(1<<bitx))

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
		
<<<<<<< HEAD
		inline uint8 get_bit(byte w, uint8 pos) {
			return _GET_BIT(w, pos);
		}
		
		inline uint8 set_bit(byte w, uint8 pos) {
			return _SET_BIT(w, pos);
		}
		
		inline uint8 clear_bit(byte w, uint8 pos) {
			return _CLEAR_BIT(w, pos);
		}
		
		inline void delay_ms(uint16 time) {
			// TODO: Implementar em assembly
=======
		inline void delay_ms(uint16 time) {
>>>>>>> 30e4a19be69aaa668739b4a668c2222fe1d955ac
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
<<<<<<< HEAD
			// TODO: Implementar em assembly
=======
>>>>>>> 30e4a19be69aaa668739b4a668c2222fe1d955ac
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
		
		inline void delay_ms_static(const uint16 time) {
			_delay_ms(time);
		}
		
		inline void delay_us_static(const uint16 time) {
			_delay_us(time);
		}
		
	}
	
}

#endif /* UTIL_H_ */