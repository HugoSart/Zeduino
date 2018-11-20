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
typedef uint32_t uint32;
typedef int32_t int32;

void * operator new(size_t size) {
	return malloc(size);	
}

void operator delete(void *ptr) {
	free(ptr);
}

namespace zeduino {
	
	namespace util {
		
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
			while (time > 0) {
				_delay_ms(1);
				time--;
			}
		}
		
		inline void delay_us(uint16 time) {
			// TODO: Implementar em assembly
			while (time > 0) {
				_delay_us(1);
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