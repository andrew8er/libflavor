/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_ADC_H_
#define	FLAVOR_ADC_H_


#include <avr/io.h>
#include <stdint.h>

namespace flavor
{
	
class Adc {
	Adc(const Adc& adc) {};
	
	static const uint8_t AdmuxReferenceVoltageMask = (1<<REFS1) | (1<<REFS0);
	static const uint8_t AdmuxChannelMask = (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	static const uint8_t AdcsraPrescalerMask = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
public:
	enum class ReferenceVoltage : uint8_t
	{
		ArefPin = 0,
		AvccPin = (1<<REFS0),
		Internal = (1<<REFS1) | (1<<REFS0)
	};
	
	enum class Justification : uint8_t
	{
		Right = 0,
		Left = (1<<ADLAR)
	};
	
	enum class Prescaler : uint8_t
	{
		Prescaler2 = (1<<ADPS0),
		Prescaler4 = (1<<ADPS1),
		Prescaler8 = (1<<ADPS1) | (1<<ADPS0),
		Prescaler16 = (1<<ADPS2),
		Prescaler32 = (1<<ADPS2) | (1<<ADPS0),
		Prescaler64 = (1<<ADPS2) | (1<<ADPS1),
		Prescaler128 = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)
	};
	
	enum class Channel : uint8_t
	{
		SingleEnded_0 = 0,
		SingleEnded_1 = (1<<MUX0),
		SingleEnded_4 = (1<<MUX2),
		SingleEnded_5 = (1<<MUX2) | (1<<MUX0),
		SingleEnded_6 = (1<<MUX2) | (1<<MUX1),
		SingleEnded_7 = (1<<MUX2) | (1<<MUX1) | (1<<MUX0),
		
#ifdef MUX5
		SingleEnded_8 = (1<<MUX5),
		SingleEnded_9 = (1<<MUX5) | (1<<MUX0),
		SingleEnded_10 = (1<<MUX5) | (1<<MUX1),
		SingleEnded_11 = (1<<MUX5) | (1<<MUX1) | (1<<MUX0),
		SingleEnded_12 = (1<<MUX5) | (1<<MUX2),
		SingleEnded_13 = (1<<MUX5) | (1<<MUX2) | (1<<MUX0),
#endif	
		// TODO: double ended, temperature sensor, etc
	};
	
	Adc() {};
	
	inline void enable();
	inline void disable();

	inline void configure(ReferenceVoltage reference, Justification justification,
	                      Prescaler factor);
	inline void setChannel(Channel channel);
	inline void startConversion();
	inline bool hasResult();
	inline void doneResultAndResetPendingInterrupt();
	inline void enableInterrupt(bool value);
	inline uint8_t readSingleEnded8();
	inline uint16_t readSingleEnded10();
};

}


void flavor::Adc::enable()
{
	ADCSRA |= (1<<ADEN);
}

void flavor::Adc::disable()
{
	ADCSRA &= ~(1<<ADEN);	
}

void flavor::Adc::setChannel(Channel channel)
{
	ADMUX = (ADMUX & ~AdmuxChannelMask) | (static_cast<uint8_t>(channel) & AdmuxChannelMask);
#ifdef MUX5
	ADCSRB = (ADCSRB & ~(1<<MUX5)) | (static_cast<uint8_t>(channel) & (1<<MUX5));
#endif
}

void flavor::Adc::configure(ReferenceVoltage reference, Justification justification,
                            Prescaler prescaler)
{
	ADMUX = (ADMUX & ~(AdmuxReferenceVoltageMask | (1<<ADLAR))) |
			static_cast<uint8_t>(reference) | static_cast<uint8_t>(justification);
	ADCSRA = (ADCSRA & ~AdcsraPrescalerMask) |
			static_cast<uint8_t>(prescaler);
}

void flavor::Adc::startConversion()
{
	ADCSRA |= (1<<ADSC);
}

bool flavor::Adc::hasResult()
{
	return ADCSRA & (1<<ADIF);
}

void flavor::Adc::doneResultAndResetPendingInterrupt()
{
	ADCSRA |= (1<<ADIF); // yes, writing 1 to this bit clears it
}

void flavor::Adc::enableInterrupt(bool value)
{
	ADCSRA = (ADCSRA & ~(1<<ADIE)) | (value<<ADIE);
}

uint8_t flavor::Adc::readSingleEnded8()
{
	return ADCH;
}

uint16_t flavor::Adc::readSingleEnded10()
{
	return ADC;
}

#endif

