/*
* @file oisc.h
* Header file for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#ifndef OISC_H
#define OISC_H

#define MEM_SIZE  (2 << BIT_WIDTH)

template <class width_t>
class oisc
{
	public:
		oisc();
		oisc(width_t * memory);
		~oisc();
		void cycle();
		void run(width_t start_address = 0);
		void load_memory(width_t start_index, width_t end_index, width_t * memory);
		uint32_t get_width();
		width *  get_memory();
		width    get_pc();
	private:
		width_t PC;
		width_t * MEMORY;

		uint8_t memory_owner;
};
