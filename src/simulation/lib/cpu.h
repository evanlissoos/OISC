/*
* @file interactive_oisc.h
* Header file for CPU info
*
* @author:  Evan Lissoos
* @date Created:  8/13/17
*/

#ifndef CPU_H
#define CPU_H

// Defines type for bit width of CPU
#define uwidth_t	uint16_t
#define width_t	  int16_t

// Landmark memory locations
// Negone location
#define NEG_ONE           0x3
// Posone location
#define POS_ONE           0x4
// Keyboard addresses (48d)
#define KEYBOARD_FLAG	    0x5
#define KEYBOARD_DATA	    0x6
// Data addresses     (64d)
#define DISPLAY_FLAG	    0x7
#define DISPLAY_DATA	    0x8
// Where programs get loaded
#define LOAD_ADDRESS	    0x10

// CPU parameters dependent on other fields
#define BIT_WIDTH		    (8 * sizeof(uwidth_t))
#define MEM_SIZE		    (1 << BIT_WIDTH)
#define MAX_PROGRAM_SIZE (MEM_SIZE - LOAD_ADDRESS)


#endif //CPU_H
