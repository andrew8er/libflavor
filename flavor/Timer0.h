/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_TIMER0_H_
#define	FLAVOR_TIMER0_H_

#include <stdint.h>
#include <avr/io.h>

namespace flavor
{
	
class Timer0
{
	Timer0(const Timer0& orig) {};
	
	static const uint8_t TCRxA_WaveForm_Mask = (1<<WGM01) | (1<<WGM00);
	static const uint8_t TCRxB_WaveForm_Mask = (1<<WGM02);
	static const uint8_t CompareMatchModeA_Mask = (1<<COM0A0) | (1<<COM0A1);
	static const uint8_t CompareMatchModeB_Mask = (1<<COM0B0) | (1<<COM0B1);
	static const uint8_t ClockSelectMask = (1<<CS02) | (1<<CS01) | (1<<CS00);
	
public:
	enum class WaveFormGenerationMode : uint8_t
	{
		Normal = 0,
		Pwm = (1<<WGM00),
		Ctc = (1<<WGM01),
		FastPwm = (1<<WGM01) | (1<<WGM00),
		PwmOcrA = (1<<WGM02) | (1<<WGM00),
		FastPwmOcrA = (1<<WGM02) | (1<<WGM01) | (1<<WGM00)
	};
	
	enum class ClockSource : uint8_t
	{
		Off = 0,
		NoPrescaler = (1<<CS00),
		Prescaler8 = (1<<CS01),
		Prescaler64 = (1<<CS01) | (1<<CS00),
		Prescaler256 = (1<<CS02),
		Prescaler1024 = (1<<CS02) | (1<<CS00),
		ExternalT0Falling = (1<<CS02) | (1<<CS01),
		ExternalT0Raising = (1<<CS02) | (1<<CS01) | (1<<CS00)
	};
	
	enum class CompareMatchModeA : uint8_t
	{
		Off = 0,
		Toggle = (1<<COM0A0),
		Clear = (1<<COM0A1),
		Set = (1<<COM0A1) | (1<<COM0A0)
	};
	
	enum class CompareMatchModeB : uint8_t
	{
		Off = 0,
		Toggle = (1<<COM0B0),
		Clear = (1<<COM0B1),
		Set = (1<<COM0B1) | (1<<COM0B0)
	};
	
	Timer0() {};
	
	inline void configure(WaveFormGenerationMode waveFormMode, ClockSource clockSource,
	                      CompareMatchModeA compareModeA, CompareMatchModeB compareModeB);
	inline void setOutputCompareA(uint8_t value);
	inline void setOutputCompareB(uint8_t value);
	inline void enableOutputCompareAInterrupt(bool value);
	inline void enableOutputCompareBInterrupt(bool value);
	inline void enableOverflowInterrupt(bool value);
};

}

void flavor::Timer0::configure(WaveFormGenerationMode waveFormMode, ClockSource clockSource,
                      CompareMatchModeA compareModeA, CompareMatchModeB compareModeB)
{
	TCCR0A = (TCCR0A & ~(CompareMatchModeA_Mask | CompareMatchModeB_Mask | TCRxA_WaveForm_Mask)) |
			static_cast<uint8_t>(compareModeA) |
			static_cast<uint8_t>(compareModeB) |
			(static_cast<uint8_t>(waveFormMode) & TCRxA_WaveForm_Mask);
	TCCR0B = (TCCR0B & ~(TCRxB_WaveForm_Mask | ClockSelectMask)) |
			(static_cast<uint8_t>(waveFormMode) & TCRxB_WaveForm_Mask) |
			static_cast<uint8_t>(clockSource);
}

void flavor::Timer0::setOutputCompareA(uint8_t value)
{
	OCR0A = value;
}

void flavor::Timer0::setOutputCompareB(uint8_t value)
{
	OCR0B = value;
}

void flavor::Timer0::enableOutputCompareAInterrupt(bool value)
{
	TIMSK0 = (TIMSK0 & ~(1<<OCIE0B)) | (value<<OCIE0A);
}

void flavor::Timer0::enableOutputCompareBInterrupt(bool value)
{
	TIMSK0 = (TIMSK0 & ~(1<<OCIE0B)) | (value<<OCIE0B);
}

void flavor::Timer0::enableOverflowInterrupt(bool value)
{
	TIMSK0 = (TIMSK0 & ~(1<<TOIE0)) | (value<<TOIE0);
}

#endif

