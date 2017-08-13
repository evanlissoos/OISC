/*
* @file oisc.h
* Header file for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#ifndef OISC_H
#define OISC_H

#include <cstdint>
#include "cpu.h"

class oisc
{
	public:
		// Constructiors and destructors
		oisc();
		oisc(volatile width_t * mem);
		~oisc();
		// Setup and run functions
		void run(width_t start_address = 0);
		void load_memory(width_t start_address, width_t end_address, width_t * data);
		// Getters
		volatile width_t *  get_memory();
		width_t    get_pc();
	protected:
		// Simulation function
		void cycle();
		// Attributes
		width_t   pc;
		volatile width_t * memory;
		uint8_t   memory_owner;
};

// Helpers
void zero_mem(volatile width_t * mem);

#endif //OISC_H
