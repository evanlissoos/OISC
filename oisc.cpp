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
	MEMORY = new width_t[sizeof(2 << width_t)];
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

void oisc::run(width_t start_address = 0)
{

}

void oisc::print_info(uint8_t size = 8)
{

}

void oisc::load_memory(width_t start_index, width_t end_index, width_t * memory)
{

}

uint32_t oisc::get_width()
{
	
}
