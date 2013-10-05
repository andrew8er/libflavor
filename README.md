libflavor
=========

libflavor is a no fuss AVR abstraction and utility library in C++. Handles various aspects of
your AVR, like timers, SPI, ADC, pins and ports.

Currently developed on an Atmega32u4, but most of it would work on other Atmegas
as well.

prerequisites
-------------
* avr-g++ 4.6.2

usage
-----
* Add the libflavor/flavor to your include and build path.
* compile the code with -std=c++0x

extending
---------
I develop this software for my own needs. Still I would like to be it as generally
useful and encompassing as possible as long as it does not lead to wicked code/preprocessor
stunts.

Feel free to fork and send me your pull request.


André Wachter