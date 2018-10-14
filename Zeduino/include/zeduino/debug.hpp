/*
 * debug.h
 *
 * Created: 10/10/2018 11:13:09
 *  Author: hugo_
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdarg.h>
#include "serial/uart.h"

namespace zeduino {
	
	namespace debug {
		
		void log(const char *format, ...) {
			va_list args;
			va_start(args, format);
			printf(format, args);
			va_end(args);
		}
		
	}
	
}



#endif /* DEBUG_H_ */