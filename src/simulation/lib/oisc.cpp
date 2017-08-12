/*
* @file xc.cpp
* Implementation for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#include "oisc.h"
#include <string>

// helpers implementation
void zero_mem(volatile width_t * mem)
{
	memset((void*) mem, 0, MEM_SIZE * sizeof(width_t));
}

// oisc implementation
oisc::oisc()
{
	pc = 0;
	memory = new width_t[MEM_SIZE];
	zero_mem(memory);
	memory_owner = true;
}

oisc::oisc(volatile width_t * mem)
{
	pc = 0;
	memory = mem;
	memory_owner = false;
}

oisc::~oisc()
{
	if(memory_owner)	delete memory;
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

void oisc::run(width_t start_address)
{
	pc = start_address;
	while(pc >= 0)	cycle();
}

void oisc::load_memory(width_t start_address, width_t end_address, width_t * data)
{
	memcpy((void *) (memory + (start_address * sizeof(width_t))), (void *) data, (end_address - start_address) * sizeof(data));
}

volatile width_t * oisc::get_memory()
{
	return memory;
}

width_t oisc::get_pc()
{
	return pc;
}
