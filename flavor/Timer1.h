/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* 
 * Author: André Wachter
 */

#ifndef FLAVOR_TIMER1_H_
#define	FLAVOR_TIMER1_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/atomic.h>

namespace flavor
{
	
class Timer1
{
	Timer1(const Timer0& orig) {};
	
	static const uint8_t WaveForm_Mask_TCRxA = (1<<WGM11) | (1<<WGM10);
	static const uint8_t WaveForm_Mask_TCRxB = (1<<WGM13) | (1<<WGM12);
	static const uint8_t CompareMatchModeA_Mask = (1<<COM1A1) | (1<<COM1A0);
	static const uint8_t CompareMatchModeB_Mask = (1<<COM1B1) | (1<<COM1B0);
	static const uint8_t CompareMatchModeC_Mask = (1<<COM1C1) | (1<<COM1C0);
	static const uint8_t ClockSelectMask_TCCRxB = (1<<CS02) | (1<<CS01) | (1<<CS00);
	
public:
	enum class WaveFormGenerationMode : uint8_t
	{
		Normal = 0,
		Pwm8 = (1<<WGM10),
		Pwm9 = (1<<WGM11),
		Pwm10 = (1<<WGM11) | (1<<WGM10),
		CtcToOcrnA = (1<<WGM12),
		FastPwm8 = (1<<WGM12) | (1<<WGM10),
		FastPwm9 = (1<<WGM12) | (1<<WGM11),
		FastPwm10 = (1<<WGM12) | (1<<WGM11) | (1<<WGM10),
		PwmPhaseAndFrequencyCorrectToIcr = (1<<WGM13),
		PwmPhaseAndFrequencyCorrectToOcrnA = (1<<WGM13) | (1<<WGM10),
		PwmPhaseCorrectToIcr = (1<<WGM13) | (1<<WGM11),
		PwmPhaseCorrectToOcrnA = (1<<WGM13) | (1<<WGM11) | (1<<WGM10),
		CtcToICrn = (1<<WGM13) | (1<<WGM12),
		FastPwmToIcrn = (1<<WGM13) | (1<<WGM12) | (1<<WGM11),
		FastPwmOCRnA = (1<<WGM13) | (1<<WGM12) | (1<<WGM11) | (1<<WGM10)
	};
	
	enum class ClockSource : uint8_t
	{
		Off = 0,
		NoPrescaler = (1<<CS10),
		Prescaler8 = (1<<CS11),
		Prescaler64 = (1<<CS11) | (1<<CS10),
		Prescaler256 = (1<<CS12),
		Prescaler1024 = (1<<CS12) | (1<<CS10),
		ExternalT0Falling = (1<<CS12) | (1<<CS11),
		ExternalT0Raising = (1<<CS12) | (1<<CS11) | (1<<CS10)
	};
	
	enum class CompareMatchModeA : uint8_t
	{
		Off = 0,
		Toggle = (1<<COM1A0),
		Clear = (1<<COM1A1),
		Set = (1<<COM1A1) | (1<<COM1A0)
	};
	
	enum class CompareMatchModeB : uint8_t
	{
		Off = 0,
		Toggle = (1<<COM1B0),
		Clear = (1<<COM1B1),
		Set = (1<<COM1B1) | (1<<COM1B0)
	};
	
	enum class CompareMatchModeC : uint8_t
	{
		Off = 0,
		Toggle = (1<<COM1B0),
		Clear = (1<<COM1B1),
		Set = (1<<COM1B1) | (1<<COM1B0)
	};
	
	Timer1() {};
	
	inline void configure(WaveFormGenerationMode waveFormMode,
						  ClockSource clockSource,
						  CompareMatchModeA compareModeA,
						  CompareMatchModeB compareModeB,
						  CompareMatchModeC compareModeC);
	inline uint16_t counter();
	inline uint16_t readCounterAtomic();
	inline void setOutputCompareA(uint16_t value);
	inline void setOutputCompareAAtomic(uint16_t value);
	inline void setOutputCompareB(uint16_t value);
	inline void setOutputCompareBAtomic(uint16_t value);
	inline void setOutputCompareC(uint16_t value);
	inline void setOutputCompareCAtomic(uint16_t value);
	
	inline void setInputCaptureAtomic(uint16_t value);
	
	inline void enableOverflowInterrupt(bool value);
	inline void enableInputCaptureInterrupt(bool value);
	inline void enableOutputCompareAInterrupt(bool value);
	inline void enableOutputCompareBInterrupt(bool value);
	inline void enableOutputCompareCInterrupt(bool value);
};

}

void flavor::Timer1::configure(WaveFormGenerationMode waveFormMode,
                       ClockSource clockSource,
                       CompareMatchModeA compareModeA,
                       CompareMatchModeB compareModeB,
                       CompareMatchModeC compareModeC)
{
	TCCR1A = (TCCR1A & ~(CompareMatchModeA_Mask | CompareMatchModeB_Mask | CompareMatchModeC_Mask | 
	         WaveForm_Mask_TCRxA)) |
	         static_cast<uint8_t>(compareModeA) |
	         static_cast<uint8_t>(compareModeB) |
	         static_cast<uint8_t>(compareModeC) |
	         (static_cast<uint8_t>(waveFormMode) & WaveForm_Mask_TCRxA);
	TCCR1B = (TCCR1B & ~(WaveForm_Mask_TCRxB | ClockSelectMask_TCCRxB)) |
	         (static_cast<uint8_t>(waveFormMode) & WaveForm_Mask_TCRxB) |
	         static_cast<uint8_t>(clockSource);
}

uint16_t flavor::Timer1::counter()
{
	return TCNT1;
}

uint16_t flavor::Timer1::readCounterAtomic()
{
	unsigned int i;
	ATOMIC_BLOCK( ATOMIC_FORCEON ) {
		i = TCNT1;
	}
	return i;
}

void flavor::Timer1::setInputCaptureAtomic(uint16_t value)
{
	ATOMIC_BLOCK( ATOMIC_FORCEON ) {
		ICR1 = value;
	}
}

void flavor::Timer1::setOutputCompareA(uint16_t value)
{
	OCR1A = value;
}

void flavor::Timer1::setOutputCompareAAtomic(uint16_t value)
{
	ATOMIC_BLOCK( ATOMIC_FORCEON ) {
		OCR1A = value;
	}
}

void flavor::Timer1::setOutputCompareB(uint16_t value)
{
	OCR1B = value;
}

void flavor::Timer1::setOutputCompareBAtomic(uint16_t value)
{
	ATOMIC_BLOCK( ATOMIC_FORCEON ) {
		OCR1B = value;
	}
}

void flavor::Timer1::setOutputCompareC(uint16_t value)
{
	OCR1C = value;
}

void flavor::Timer1::setOutputCompareCAtomic(uint16_t value)
{
	ATOMIC_BLOCK( ATOMIC_FORCEON ) {
		OCR1C = value;
	}
}

void flavor::Timer1::enableOverflowInterrupt(bool value)
{
	TIMSK1 = (TIMSK1 & ~(1<<TOIE1)) | (value<<TOIE1);
}

void flavor::Timer1::enableInputCaptureInterrupt(bool value)
{
	TIMSK1 = (TIMSK1 & ~(1<<ICIE1)) | (value<<ICIE1);
}

void flavor::Timer1::enableOutputCompareAInterrupt(bool value)
{
	TIMSK1 = (TIMSK1 & ~(1<<OCIE1A)) | (value<<OCIE1A);
}

void flavor::Timer1::enableOutputCompareBInterrupt(bool value)
{
	TIMSK1 = (TIMSK1 & ~(1<<OCIE1B)) | (value<<OCIE1B);
}

void flavor::Timer1::enableOutputCompareCInterrupt(bool value)
{
	TIMSK1 = (TIMSK1 & ~(1<<OCIE1C)) | (value<<OCIE1C);
}

#endif

