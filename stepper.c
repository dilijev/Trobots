#include "head.h"

#define WHEEL_STEP 200

unsigned char LeftDir=0, RightDir=0;

void Stepper_Init(void)
{
	asm sei;
	
	TIOS |= 0x01; // activate OC0
	TIE |= 0x01; // arm OC0

	// first interrupt after 42ns
	TC0 = TCNT+1; 
	
	// clear C0F
	TFLG1 |= 0x01;
}
           
static const byte SEQ[] = { 5,4,6,2,10,8,9,1 };
static byte inLeft = 0, inRight = 0;
static byte left=0,right=0;
           
interrupt 8 void _moveWheels(void) {
  byte output = PTT;

  TFLG1 |= 0x01;
  TC0 += WHEEL_STEP;  
  if(LeftDir) {
    left = 0x07 & (left + inLeft);
    output &= 0xF0;
    output |= SEQ[left];
  }
  
  if(RightDir) {
    right = 0x07 & (right + inRight);
    output &= 0x0F;
    output |= SEQ[right]<<4;
  }

  inLeft = LeftDir;
  PTT = output;
}