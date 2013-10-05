/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_PIN_H_
#define	FLAVOR_PIN_H_

#include <avr/io.h>
#include <stdint.h>

namespace flavor
{

template<class P, uint8_t N>
class Pin
{
public:
	Pin() {};
	
	inline void setOutput() const;
	inline void setInput() const;
	inline void off() const;
	inline void on() const;
	inline void toggle() const;
	inline void set(bool value) const;
	inline bool read() const;
};

}

template<class P, uint8_t N>
void flavor::Pin<P, N>::setOutput() const
{
//	*(P::DDRx) |= (1<<N);
	P::DDRx |= (1<<N);
}

template<class P, uint8_t N>
void flavor::Pin<P, N>::setInput() const
{
	P::DDRx &= ~(1<<N);
}

template<class P, uint8_t N>
void flavor::Pin<P, N>::off() const
{
	P::PORTx &= ~(1<<N);
}

template<class P, uint8_t N>
void flavor::Pin<P, N>::on() const
{
	P::PORTx |= (1<<N);
}

template<class P, uint8_t N>
void flavor::Pin<P, N>::toggle() const
{
	P::PORTx ^= (1<<N);
}

template<class P, uint8_t N>
void flavor::Pin<P, N>::set(bool value) const
{
	P::PORTx = (P::PORTx & (1<<N)) | (value<<N);
}

template<class P, uint8_t N>
bool flavor::Pin<P, N>::read() const
{
	return P::PINx & (1<<N);
}

#endif


