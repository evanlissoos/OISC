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
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std::string_literals;

#define width_t    uint16_t

#define BIT_WIDTH  (8 * sizeof(width_t))
#define MEM_SIZE   (1 << BIT_WIDTH)


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

class interactive_oisc: public oisc
{
	// Interactive functions
	public:
		void run(volatile uint8_t *continue_running, width_t start_address = 0);
		void run(width_t start_address = 0);
	private:
		uint8_t get_input();
};

#endif //OISC_H
