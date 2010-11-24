// filename ******** Main.C ************** 
// This example illustrates the running Trobot in C, 
// 9S12DP512                
// Jonathan W. Valvano 11/20/10

// Configure this project for your tank (do this once)
// 1) Open the Edit->HCS12SerialMonitorSettings, 
// 2) click "Linker for HC12"
// 3) Place your team name in the "Application Filename" field 
//    E.g., change "z3.abs" to "a0.abs"
//  The rest of the instructions assume you are team z3

// To run this program in TExaS
// 0) Double click Texas.uc file in bin folder to start TExaS
// 1) In Metrowerks, Execute Project->Make to compile C code
//   This creates a bunch of files in the bin directory
//       an object code     z3.sx
//       listing files      main.lst start12.lst plus your files
//       map file           z3.map
// 2) Within TExaS import these files, execute Action->OpenS19
//    select z3.sx in the bin folder
//  (Subsequent times you can execute Action->OpenS19Again)
// 3) Debug using usual TExaS debugging features   

// To run this program in TRobot simulator
// 1) Execute Project->Make to compile C code
//   This creates a bunch of files in the bin directory
//       an object code     HCS12_Serial_Monitor.sx
//       listing files      main.lst timer.lst sci.lst start.lst
//       map file           HCS12_Serial_Monitor.map
// 2) move z3.sx to the S19 folder of TRobots
// 3) Rename this sx file to match your tank code (e.g., z3.sx)
// 4) Run TRobots   

#include <hidef.h>      /* common defines and macros */
#include <mc9s12dp512.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12dp512"

//****DO NOT PUT ANYTHING RAM DEFINITIONS HERE ******
// these first 8 bytes are observable in TRobot
unsigned char volatile Mem3800[8];  // this will be at address $3800
#define WatchByte0 *(unsigned char volatile *)(0x3800)
#define WatchByte1 *(unsigned char volatile *)(0x3801)
#define WatchByte2 *(unsigned char volatile *)(0x3802)
#define WatchByte3 *(unsigned char volatile *)(0x3803)
#define WatchByte4 *(unsigned char volatile *)(0x3804)
#define WatchByte5 *(unsigned char volatile *)(0x3805)
#define WatchByte6 *(unsigned char volatile *)(0x3806)
#define WatchByte7 *(unsigned char volatile *)(0x3807)
// these macros can be used to observe 16-bit values
#define WatchWord0	*(unsigned short volatile *)(0x3800)
#define WatchWord1	*(unsigned short volatile *)(0x3802)
#define WatchWord2	*(unsigned short volatile *)(0x3804)
#define WatchWord3	*(unsigned short volatile *)(0x3806)

//****PUT YOUR INCLUDES BELOW HERE*************

//---------Wait------------------
// fixed time delay
// inputs: time to wait in 40ns cycles
// outputs: none
void Wait(unsigned short delay){ 
unsigned short startTime;
  startTime = TCNT;
  while((TCNT-startTime) <= delay){} 
}
void main(void) { 
  Mem3800[0] = 0; // leave this so the compiler will not remove it
  WatchWord1 = 0;
  WatchWord2 = 0; 
  TSCR1 = 0x80;     // Enable TCNT, 25MHz E clock
  TSCR2 = 0x00;     // divide by 1 TCNT prescale, TOI disarm
  PACTL = 0;        // timer prescale used for TCNT
  DDRT = 0xFF;      // PTT7-4 are left track, PTT3-0 are right track
  PTT = 0x55;       // activate two track stepper coils
  DDRM = 0x3F;      // PTM5,4 = sensor resolution, PTM3-0 are turret
  PTM = 0x05;       // narrow resolution activate turret stepper 
  EnableInterrupts; 
  for(;;) {     
    for(WatchByte1=10; WatchByte1; WatchByte1=WatchByte1-1){
// straight
      Wait(220); 
      PTT = 0x66; // forward
      Wait(220);
      PTT = 0xAA; // forward
      Wait(220);
      PTT = 0x99; // forward
      Wait(220);
      PTT = 0x55; // forward
      WatchWord1 = WatchWord1+1;   // **Debugging**
    }

    Wait(220);
    PTT = 0x56; // turn
    Wait(220);
    PTT = 0x5A; // turn
    Wait(220);
    PTT = 0x59; // turn
    Wait(220);
    PTT = 0x55; // turn
    WatchWord2 = WatchWord2+1;  // **Debugging**
  //  asm stop  // breakpoint
  } 
}
