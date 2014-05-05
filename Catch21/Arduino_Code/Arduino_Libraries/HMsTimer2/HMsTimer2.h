#ifndef HMsTimer2_h
#define HMsTimer2_h

#include <avr/interrupt.h>

namespace HMsTimer2 {
	extern unsigned long hmsecs;
	extern void (*func)();
	extern volatile unsigned long count;
	extern volatile char overflowing;
	extern volatile unsigned int tcnt2;
	
	void set(unsigned long hms, void (*f)());
	void start();
	void stop();
	void _overflow();
}

#endif
