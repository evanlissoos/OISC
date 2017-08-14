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

void input_thread(volatile width_t * mem)
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

void output_thred(volatile width_t * mem)
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
