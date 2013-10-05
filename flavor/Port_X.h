/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_PORT_X_H_
#define	FLAVOR_PORT_X_H_

#include <avr/io.h>
#include <stdint.h>

namespace flavor
{

#ifdef PORTA
class Port_A
{
	Port_A() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

#ifdef PORTB
class Port_B
{
	Port_B() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

#ifdef PORTC
class Port_C
{
	Port_C() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

#ifdef PORTD
class Port_D
{
	Port_D() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

#ifdef PORTE
class Port_E
{
	Port_E() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

#ifdef PORTF
class Port_F
{
	Port_F() {};
public:
	static volatile uint8_t& PORTx;
	static volatile uint8_t& PINx;
	static volatile uint8_t& DDRx;
};
#endif

}

#endif

