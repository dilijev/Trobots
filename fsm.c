#include "head.h"

typedef const struct State {
	byte output;
	// void (*callOut)(void);
	const struct State *next[5];
} State;

#define FBACK 0
#define BACK 1
#define STAY 2
#define FWD 3
#define FFWD 4

#define S0 &fsm[0] // 5
#define S1 &fsm[1] // 4
#define S2 &fsm[2] // 6
#define S3 &fsm[3] // 2
#define S4 &fsm[4] // 10
#define S5 &fsm[5] // 8
#define S6 &fsm[6] // 9
#define S7 &fsm[7] // 1

#define NUM_STATES 8

State fsm[] = {
	/* transitions for types of movement: */
	/* FBACK,BACK,STAY,FWD,FFWD */
	/*S0*/ { 5, {S6,S7,S0,S1,S2} },
	/*S1*/ { 4, {S0,S0,S1,S2,S2} },
	/*S2*/ { 6, {S0,S1,S2,S3,S4} },
	/*S3*/ { 2, {S2,S2,S3,S4,S4} },
	/*S4*/ { 10,{S2,S3,S4,S5,S6} },
	/*S5*/ { 8, {S4,S4,S5,S6,S6} },
	/*S6*/ { 9, {S4,S5,S6,S7,S0} },
	/*S7*/ { 1, {S6,S6,S7,S0,S0} },
};

State *leftState = S0;
State *rightState = S0;
State *turretState = S0;

byte leftStep = STAY;
byte rightStep = STAY;
byte turretStep = STAY;