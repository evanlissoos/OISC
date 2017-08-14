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
#include <string>
#include <fstream>
#include "cpu.h"

using namespace std;

class oisc
{
	public:
		// Constructiors and destructors
		oisc();
		oisc(volatile width_t * mem);
		virtual ~oisc();
		// Getters
		volatile width_t * get_memory();
		width_t			       get_pc();
		// Setup and run functions
		virtual void run(width_t start_address = 3);
		void	       load_memory(width_t start_address, width_t end_address, width_t * data);
		uint8_t      load_file(string filename);
		void	       zero_mem();
	protected:
		// Simulation function
		void cycle();
		// Attributes
		width_t			       pc;
		volatile width_t * memory;
		uint8_t			       memory_owner;
};

#endif //OISC_H
