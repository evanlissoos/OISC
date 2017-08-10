/*
* @file oisc.h
* Header file for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#ifndef OISC_H
#define OISC_H

#define width_t    uint16_t

#define BIT_WIDTH  (8 * sizeof(width_t))
#define MEM_SIZE   (1 << BIT_WIDTH)


class oisc
{
	public:
		// Constructiors and destructors
		oisc();
		oisc(width_t * mem);
		~oisc();
		// Setup and run functions
		void run(width_t start_address = 0);
		void load_memory(width_t start_address, width_t end_address, width_t * data);
		// Getters
		width_t *  get_memory();
		width_t    get_pc();
	protected:
		// Simulation function
		void cycle();
		// Attributes
		width_t   pc;
		width_t * memory;
		uint8_t   memory_owner;
};

class interactive_oisc: public oisc
{
	public:
		// Interactive functions
		uint8_t get_input();
		void run(width_t start_address = 0);
};
