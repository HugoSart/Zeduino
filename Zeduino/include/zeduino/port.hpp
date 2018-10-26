/*
* Port.h
*
* Created: 02/10/2018 22:04:38
*  Author: hugo_
*/
#define F_CPU 16000000UL

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
		
		inline bool read(EPort port) {
			return tst_bit(fcrin(port), nmr(port));
		}
		
		inline void toggle(EPort port) {
			if (is_enabled(port)) disable(port);
			else enable(port);
		}
		
		inline void ctc(EPort port, int freq){
			
			if(freq < 0) freq = 0;
			
			#ifdef ZEDUINO_AUTO
			mode(port, OUTPUT);
			#endif
			
			if(port == P6){
				set_bit(TCCR0A, WGM01); // Ativa o modo CTC
				set_bit(TCCR0A, COM0A0); // Configura o modo CTC = OCR0A
				OCR0A = (F_CPU/(2*freq))-1;
				}
			else if(port == P5){
				set_bit(TCCR0B, WGM01); // Ativa o modo CTC
				set_bit(TCCR0B, COM0A0); // Configura o modo CTC = OCR0B
				OCR0B = (F_CPU/(2*freq))-1;
			}			
			else {
				enable(port);
			}
		}
		
		inline void pwm(EPort port, int active_cicle){ //active_cicle 0 a 255
			
			if(active_cicle < 0) active_cicle = 0;
			if(active_cicle > 255) active_cicle = 255;
			
			#ifdef ZEDUINO_AUTO
			mode(port, OUTPUT);
			#endif
			
			if(port == P6){
				set_bit(TCCR0A, WGM00);
				set_bit(TCCR0A, WGM01); // Ativa o modo Fast PWM
				set_bit(TCCR0A, COM0A1); // Configura o modo Fast PWM como padrão não-invertido
				OCR0A = active_cicle;
			}
			else if(port == P5){
				set_bit(TCCR0B, WGM00);
				set_bit(TCCR0B, WGM01); // Ativa o modo Fast PWM
				set_bit(TCCR0B, COM0A1); // Configura o modo Fast PWM como padrão não-invertido
				OCR0B = active_cicle;
			}
			else {
				enable(port);
			}
		}
	}
	
}



#endif /* PORT_H_ */