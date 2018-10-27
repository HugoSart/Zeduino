# Zeduino
A simple high-level C++ header only library for the Atmel AVR microcontroler, focused on Arduino UNO. <br/>
This library provide a simple interface to build an executable project in small time. <br/>
This project was entirely made using Atmel Studio.

# How does it works?
This library works with components. <br/>
For now, we have 4 different components ready to use:
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

# Components
The components are implemented as classes.

Led:
- Constructor Led(EPort) has as parameter the identifier of the port to be used to set the led (P0 to P13).
- IsOn() returns true if the led is on or false in case it is not.
- TurnOn() is void type and turns on the led.
- TurnOn(bool) turns on the led if the parameter is true and turns off the led in case it is false.
- TurnOff() turns off the led.
- Toggle() turns on and off the led according to the previous state of it.
- Blink(uint16) makes the led blink according to the parameter, which an integer that sets the quantity of time the led is on and off in miliseconds.

Button:
- Constructor Button(Eport) has as parameter the identifier of the port to be used to set the button (P0 to P13).
- IsPressed() returns true if the button is pressed and false if it is not.
- JustPressed() returns true if the button have just been pressed or false if it hasn't.
- JustReleased() returns true if the button have just been released or false if it hasn't.

Display7:
- Etype can be CATHODE or ANODE.
- Constructor Display7(EType, Eport, Eport, Eport, Eport, Eport, Eport, Eport, Eport) has as parameters if it's CATHODE or ANODE and the ports from a to h.
- Constructor Display7 can also be used without the first parameter (EType), in this case the display is by default set as ANODE.
- SetDotVisibility(bool) enables the dot from the display.
- IsDotVisible() returns true if the dot is visible and false if it's not.
- SetValue(uint8) has as parameter the hexadecimal to be displayed from 0 to 15, if the value is below 0 then 0 will be displayed. If the value is above 15 then 15 will be displayed.

Sonar:
- Constructor Sonar(Eport, Eport) has as first parameter the port to be used as trigger and the second parameter is the echo port.
- ReadDistance() returns an integer that represents the distance from the sonar to the object that reflects it sound waves.

# Util.hpp
Here you can find the implementations of delay in microseconds and miliseconds.

- delay_ms(uint16) creates a delay based on the parameter value in miliseconds.
- delay_us(uint16) creates a delay based on the parameter value in microseconds.

# Port.hpp
Here you can find I/O manipulation and wave form generation.

- enum EMode can assume either INPUT or OUTPUT.
- enum EPort can assume values from P0 to P13.
- mode(EPort, EMode) sets the port from the first parameter as the mode passed on the second parameter.
- get_mode(EPort) returns the mode of the port passed as parameter.
- enable(EPort) sends high digital sign to the specified port.
- enable(EPort, bool) sends high or low digital sign if the bool is true or false, respectively.
- disable(EPort) sends low digital sign to the port.
- is_enabled(EPort) returns true if the port has high digital sign or false if it is low.
- toggle(Eport) enable the port if its disabled and the opposite if its disabled.
- ctc(EPort, int) sets the specified port to generate wave form in the frequency passed as second parameter. Only works on EPorts P5 and P6. In the other Eport it only sends digital sign.
- pwm(Eport, int) sets the specified port to generate pwm and the second parameter establishes the active cycle duty. It can be from 0 to 255, where 0 represents 0% and 255 represents 100% of active cycle duty. Also only works on Eports P5 and P6. Other ports only sends digital sign.
