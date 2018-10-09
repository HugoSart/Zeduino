/*
 * display7decoder.h
 *
 * Created: 09/10/2018 00:04:14
 *  Author: hugo_
 */ 


#ifndef DISPLAY7DECODER_H_
#define DISPLAY7DECODER_H_

namespace zeduino {
	namespace util {
		
		EPort[] encode(uint8 hex) {
			if (hex == 0) {
				EPort ports[6] = {P0, P1, P2, P3, P4, P5};
				return ports;
			}
		}
		
	}
}

#endif /* DISPLAY7DECODER_H_ */