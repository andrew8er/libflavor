/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_SPI_H_
#define	FLAVOR_SPI_H_

#include <stdint.h>
#include <avr/io.h>

namespace flavor
{

class SPI
{
public:
	SPI(const SPI& orig);
	
	enum class DataOrder : uint8_t
	{
		MsbFirst = 0,
		LsbFirst = (1<<DORD)
	};
	
//	enum class Mode : uint8_t
//	{
//		Slave = 0,
//		Master = (1<<MSTR)
//	};
	
	enum class ClockRate : uint8_t
	{
		F4 = 0,
		F16 = (1<<SPR0),
		F64 = (1<<SPR1),
		F128 = (1<<SPR1) | (1<<SPR0)
	};
	
	enum class ClockPolarity : uint8_t
	{
		LeadingEdgeRising = 0,
		LeadingEdgeFalling = (1<<CPOL)
	};
	
	enum class ClockPhase : uint8_t
	{
		SampleLeadingEdge = 0,
		SampleTrailingEdge = (1<<CPHA)
	};
	
	
	SPI() {};
	
	inline void enable();
	inline void disable();
	
	inline void setInterruptEnabled(bool value);
	inline void configureMaster(ClockRate rate, bool doubleSpeed, DataOrder order,
	                            ClockPolarity polarity, ClockPhase phase);
	inline void enableWriteCompleteInterrupt(bool value);
	
	inline void write(uint8_t data);
};

}

void flavor::SPI::configureMaster(ClockRate rate, bool doubleSpeed, DataOrder order,
                          ClockPolarity polarity, ClockPhase phase)
{
	// TODO double speed
	SPCR = (SPCR & ~((1<<DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR1) | (1<<SPR0))) |
	       static_cast<uint8_t>(order) |
	       (1<<MSTR) |
	       static_cast<uint8_t>(rate) |
	       static_cast<uint8_t>(polarity) |
	       static_cast<uint8_t>(phase);
}

void flavor::SPI::enableWriteCompleteInterrupt(bool value)
{
	SPCR = (SPCR & ~(1<<SPIE)) | (value<<SPIE);
}

void flavor::SPI::enable()
{
	SPCR |= (1<<SPE);
}

void flavor::SPI::disable()
{
	SPCR &= ~(1<<SPE);
}

void flavor::SPI::setInterruptEnabled(bool value)
{
	SPCR = (SPCR & ~(1<<SPIE)) | (value<<SPIE);
}

void flavor::SPI::write(uint8_t data)
{
	SPDR = data;
}

#endif

