/*
* @file interactive_oisc.h
* Header file for memory mapped IO
*
* @author:  Evan Lissoos
* @date Created:  8/13/17
*/

#ifndef MEM_IO_H
#define MEM_IO_H

#include "cpu.h"
#include <iostream>
#include <string>

using namespace std;

/*
* input_thread
*
* description: Thread that handles keyboard input
* arguments  : mem - pointer to memory block
* returns    : None
*/
void input_thread(volatile uwidth_t * mem)
{
	while(1)
	{
		// Getting a raw charachter from keyboard input
		system("/bin/stty raw");
		char c = getchar();
		system("/bin/stty cooked");

		if(c == 3)	return;

		// Setting the data memory
		mem[KEYBOARD_FLAG] = (uint16_t) 1;
		// Setting the flag signaling data is ready
		// NOTE: It is up to the CPU to handle lowering this flag
		mem[KEYBOARD_DATA] = (uint16_t) c;
	}
}

/*
* output_thread
*
* description: Thread that handles terminal output
* arguments  : mem - pointer to memory block
* returns    : None
*/
void output_thred(volatile uwidth_t * mem)
{
	while(1)
	{
		// First, check if data is ready
		if(mem[DISPLAY_FLAG])
		{
			// Writing the charachter to the screen
			cout << (char) mem[DISPLAY_DATA];
			// Lower flag as the data has been written
			mem[DISPLAY_FLAG] = 0;
		}
	}
}

#endif //MEM_IO_H
