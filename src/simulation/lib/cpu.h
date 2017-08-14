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
#define width_t	uint16_t

// Landmark memory locations
// Where programs gets loaded
#define LOAD_ADDRESS	    0x42
// Keyboard addresses (48d)
#define KEYBOARD_FLAG	 0x30
#define KEYBOARD_DATA	 0x31
// Data addresses     (64d)
#define DISPLAY_FLAG	    0x40
#define DISPLAY_DATA	    0x41
// Negone location
#define NEG_ONE           0x35
// Posone location
#define POS_ONE           0x36

// CPU parameters dependent on other fields
#define BIT_WIDTH		    (8 * sizeof(width_t))
#define MEM_SIZE		    (1 << BIT_WIDTH)
#define MAX_PROGRAM_SIZE (MEM_SIZE - LOAD_ADDRESS)


#endif //CPU_H
