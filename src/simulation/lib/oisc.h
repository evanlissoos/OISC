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
		oisc(volatile uwidth_t * mem);
		virtual ~oisc();
		// Getters
		volatile uwidth_t * get_memory();
		uwidth_t			       get_pc();
		// Setup and run functions
		virtual void run(uwidth_t start_address = LOAD_ADDRESS);
		void	       load_memory(uwidth_t start_address, uwidth_t end_address, uwidth_t * data);
		uint8_t      load_file(string filename);
		void	       zero_mem();
	protected:
		// Simulation function
		void cycle();
		// Initialization function
		void init();
		// Attributes
		uwidth_t			      pc;
		volatile uwidth_t * memory;
		uint8_t			        memory_owner;
};

#endif //OISC_H
