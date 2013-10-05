/* 
 * Author: André Wachter
 * 
 * Created on September 23, 2013, 9:43 PM
 */

#include "Port_X.h"
#include <avr/io.h>

#ifdef PORTA
volatile uint8_t& flavor::Port_A::PORTx = PORTA;
volatile uint8_t& flavor::Port_A::PINx = PINA;
volatile uint8_t& flavor::Port_A::DDRx = DDRA;
#endif

#ifdef PORTB
volatile uint8_t& flavor::Port_B::PORTx = PORTB;
volatile uint8_t& flavor::Port_B::PINx = PINB;
volatile uint8_t& flavor::Port_B::DDRx = DDRB;
#endif

#ifdef PORTC
volatile uint8_t& flavor::Port_C::PORTx = PORTC;
volatile uint8_t& flavor::Port_C::PINx = PINC;
volatile uint8_t& flavor::Port_C::DDRx = DDRC;
#endif

#ifdef PORTD
volatile uint8_t& flavor::Port_D::PORTx = PORTD;
volatile uint8_t& flavor::Port_D::PINx = PIND;
volatile uint8_t& flavor::Port_D::DDRx = DDRD;
#endif

#ifdef PORTE
volatile uint8_t& flavor::Port_E::PORTx = PORTE;
volatile uint8_t& flavor::Port_E::PINx = PINE;
volatile uint8_t& flavor::Port_E::DDRx = DDRE;
#endif

#ifdef PORTF
volatile uint8_t& flavor::Port_F::PORTx = PORTF;
volatile uint8_t& flavor::Port_F::PINx = PINF;
volatile uint8_t& flavor::Port_F::DDRx = DDRF;
#endif

