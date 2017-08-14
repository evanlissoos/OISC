/*
* @file xc.cpp
* Implementation for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#include "oisc.h"

// oisc implementation
oisc::oisc()
{
	pc = 3;
	memory = new width_t[MEM_SIZE];
	this->zero_mem();
	memory_owner = true;
}

oisc::oisc(volatile width_t * mem)
{
	pc = 3;
	memory = mem;
	memory_owner = false;
}

oisc::~oisc()
{
	if(memory_owner)	delete memory;
}

volatile width_t * oisc::get_memory()
{
	return memory;
}

width_t oisc::get_pc()
{
	return pc;
}

void oisc::run(width_t start_address)
{
	// Halting condition is PC getting to 0
	pc = start_address;
	while(pc > 0)	cycle();
}

void oisc::load_memory(width_t start_address, width_t end_address, width_t * data)
{
	memcpy((void *) (memory + (start_address * sizeof(width_t))), (void *) data, (end_address - start_address) * sizeof(data));
}

uint8_t oisc::load_file(string filename)
{
	ifstream file_in(filename, ios::in | ios::binary);
	file_in.seekg(0, file_in.end);
	width_t length = file_in.tellg();
	file_in.seekg(0, file_in.beg);

	if(length > MAX_PROGRAM_SIZE)
	{
		file_in.close();
		return 1;
	}

	file_in.read((char *) &(memory[LOAD_ADDRESS]), length);
	file_in.close();

	// Loading jump to start address at current PC location
	memory[pc]	 = 0;
	memory[pc + 1] = 0;
	memory[pc + 2] = LOAD_ADDRESS;
	return 0;
}

void oisc::zero_mem()
{
	memset((void*) memory, 0, MEM_SIZE * sizeof(width_t));
}

void oisc::cycle()
{
	width_t a, b, c;
	a = memory[pc];
	b = memory[pc + 1];
	c = memory[pc + 2];
	memory[b] = memory[b] - memory[a];
	pc = (memory[b] > 0) ? pc + 3 : c;
}
