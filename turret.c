#include "head.h"

#define TURRET_STEP 200

void Turret_Init(void)
{
	asm sei;
	
	TIOS |= 0x02; // activate OC1
	TIE |= 0x02; // arm OC1

	// first interrupt after 42ns
	TC1 = TCNT+1; 
	
	// clear C1F
	TFLG1 |= 0x02;
}

interrupt 9 void _moveTurret(void) {
	
	
	

	TC1 = TC1 + TURRET_STEP;
}