#ifndef _read_shift_
#define _read_shift_



/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the the shift registers
*/




#define NUMBER_OF_SHIFT_CHIPS   3

#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

// Width of pulse to trigger the shift register to read and latch.
#define PULSE_WIDTH_USEC   3




int ploadPin        = 7;  // Connects to Parallel load pin the 165
int clockEnablePin  = 9;  // Connects to Clock Enable pin the 165
int dataPin         = 8; // Connects to the Q7 pin the 165
int clockPin        = 14; // Connects to the Clock pin the 165

unsigned long pinValues;
unsigned long oldPinValues;

unsigned int read_shift_regs();


#endif
