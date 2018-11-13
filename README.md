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
- Display LCD 16x2;
- Digital temperature/humidity sensor;
<br/>
Also, it has functions that provides delay with variable time parameter, easy I/O manipulation (e.g. enabling a port, or set a port as input/output), wave form generation and serial communication, so feel free to use the good old printf. <br/>
Another feature is a "main" interface, replacing the default main function of your C++ code with a setup and loop function that you gonna implement (as well as Arduino).

# Example

```c++
#define ZEDUINO_LAUNCHER // This tells the compiler that you'll use the setup and loop function, 
                         // otherwise you'll need to create your own main and main loop

#include <zeduino/zeduino.hpp>

using namespace zeduino;

component::Led *led; // Simple global variable that refers to a led component

void setup() {
	// port::mode(P0, OUTPUT);    // Not necessery if ZEDUINO_AUTO is defined
	led = new component::Led(P0); // Create a new instance of Led connected to the port 0
}

// Function called inside an infinite loop
void loop() {
	led->Toggle();        // Toggle the led state (on/off)
	util::delay_ms(1000); // Wait 1 second before continue
```
# Usefull Information
This library was tested using an Arduino UNO.

# Components
The components are implemented as classes inside the namespace zeduino::component.

- Led:
  - Led(EPort e): instantitate a Led connected to the port e;
  - bool IsOn(): returns true if the led is on or false in case it is not;
  - void TurnOn(): turns on the led;
  - void TurnOn(bool on): turns the led on or off;
  - void TurnOff(): turns off the led;
  - void Toggle(): toggle the led state;
  - void Blink(uint16 time): toggle the led, waits time in millis and toggle the led again;

- Button:
  - Button(EPort e): instantiate a Button connected to the port e;
  - bool IsPressed(): returns true if the Button is current pressed;
  - bool JustPressed(): returns true if the Button was just pressed;
  - bool JustReleased(): returns true if the Button was just released;

- Sonar:
  - Sonar(EPort trigger, EPort echo);
  - uint16 ReadDistance(): measure the distance from the sensor;
  
- Display7:
  - Display7(EType, EPort a, EPort b, EPort c, EPort d, EPort e, EPort f, EPort g, EPort h): EType can be either CATHODE/ANODE;
  - void SetDotVisibility(bool visibility): set the visibility of the dot on the display;
  - bool IsDotVisible(): check if the dot is visible;
  - void SetValue(uint8 value): set the value on the display in rage of 0 and 15;
  
- DisplayLCD (4-bit):
  - DisplayLCD(EPort mode, EPort pulse, EPort ports[]);
  - void Write(char c): write a character on the current cursor position;
  - void Write(char str[]): write a string on de screen;
  - void ClearScreen(): clear the screen and reset the cursor;
  
- DHT11:
  - DHT11(EPort port);
  - void Update(): measure the sensor temperature and humidity and caches it. Must be called before any reads;
  - void ReadTemperature(): read the cached temperature;
  - void ReadHumidity(): read the cached humidity;

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
