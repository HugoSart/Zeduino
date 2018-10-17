# Zedunio
A simple high-level C++ header only library for the Atmel AVR microcontroler, focused on Arduino UNO. <br/>
This library provide a simple interface to build an executable project in small time. <br/>
This project was entirely made using Atmel Studio.

# How does it works?
This library works with components. <br/>
For now, we have 5 different components ready to use:
- Led;
- Button;
- 7 Segment Display;
- Ultrassonic Sensor;
<br/>
Also, it has functions that provides delay with variable time parameter, easy I/O manipulation (e.g. enabling a port, or set a port as input/output), wave form generation and serial communication, so feel free to use the good old printf. <br/>
Another feature is a "main" interface, replacing the default main function of your C++ code with a setup and loop function that you gonna implement (as well as Arduino).

# Example

```c++
#define F_CPU 16000000UL
#define ZEDUINO_LAUNCHER // This tells the compiler that you'll use the setup and loop function, 
                         // otherwise you'll need to create your own main and main loop
#define ZEDUINO_AUTO	 // Automatic set mode (input/output) inside components constructors;

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Led *led; // Simple global variable that refers to a led component

// Called before entering the main loop
void setup() {
	// port::mode(P0, OUTPUT);    // Not necessery if ZEDUINO_AUTO is defined
	led = new component::Led(P0); // Create a new instance of Led connected to the port 0
}

// Function called inside an infinite loop
void loop() {
	led->Toggle();        // Toggle the led state (on/off)
	util::delay_ms(1000); // Wait 1 second before continue
  // instead you can use led->Blink(1000);
}
```
# Usefull Information
This library was tested using an Arduino UNO.
