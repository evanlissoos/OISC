/*
* @file xc.cpp
* Implementation for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#include "oisc.h"
#include <iostream>
#include <stdlib>

template <class width_t>
oisc::oisc()
{
	PC = 0;
	MEMORY = new width_t[1 << (sizeof(width_t) * 8)];
	memory_owner = true;
}

template <class width_t>
oisc::oisc(width_t * memory)
{
	PC = 0;
	MEMORY = memory;
	memory_owner = false;
}

oisc::~oisc()
{
	if(memory_owner)
		free(memory);
}

void oisc::cycle()
{
	width_t a, b, c;
	a = MEMORY[PC];
	b = MEMORY[PC + 1];
	c = MEMORY[PC + 2];
	MEMORY[b] = MEMORY[b] - MEMORY[a];
	PC = (MEMORY[b] > 0) ? PC + 3 : c;
}

void oisc::run(width_t start_address = 0)
{
	PC = start_address;
	while(PC >= 0)	cycle();
}

//Print needs to be a user implemented function
//void oisc::print_info(uint8_t size = 8)

void oisc::load_memory(width_t start_index, width_t end_index, width_t * memory)
{

}

width_t * oisc::get_memory()
{
	return MEMORY;
}

width_t oisc::get_pc()
{
	return PC:
}

uint32_t oisc::get_width()
{
	return sizeof(width_t);
}
