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
#include <string>

// Helpers
static std::vector<std::string> * split_string(std::string input_string)
{
	std::vector<string> * ret = new std::vector<string>;
	std::string str;
	for(uint32_t i = 0; i < input_string.length(); i++)
	{
		if(input_string[i] != ' ')
			str += input_string[i];
		else
		{
			ret->push_back(str);
			str = "";
		}
	}
	return ret;
}

static uint8_t is_in(std::string &value, std::vector<std::string> &list)
{
	// Ooo look at me I'm hot shit becasue I can interate
	for(auto it = list.begin(); it != list.end(); ++it)
		if(*it == value)	return true;
	return false;
}

static void print_location(width_t location, width_t value)
{
	std::cout << std::showbase << std::internal << std::setfill('0');
	std::cout << std::hex << std::setw(sizeof(width_t)) << location << std::dec << ": "
						<< std::hex << std::setw(sizeof(width_t)) << value << std::dec << std::endl;
}

static width_t parse_literal(std::string &literal)
{
	if(literal.find("0x") == 0 || literal.find("0X") == 0)
		return std::stoi(literal, 0, 16);
	else if(literal.find("0b") == 0 || literal.find("0B") == 0)
		return std::stoi(literal.substr(2), 0, 2);
	else if(literal.find("0h") == 0 || literal.find("0H") == 0)
		return std::stoi(literal.substr(2), 0, 8);
	else
		return std::stoi(literal);
}

static void zero_mem(volatile width_t * mem)
{
	memset(mem, 0, MEM_SIZE * sizeof(width_t));
}

static uint8_t invalid_input(std::string &error_msg)
{
	std::cout << "Invalid input: " << error_msg << std::endl;
	return 0;
}

// oisc implementation
oisc::oisc()
{
	pc = 0;
	memory = new width_t[MEM_SIZE];
	zero_mem(memory);
	memory_owner = true;
}

oisc::oisc(width_t * mem)
{
	pc = 0;
	memory = mem;
	memory_owner = false;
}

oisc::~oisc()
{
	if(memory_owner) free(memory);
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

void oisc::run(width_t start_address = 0)
{
	pc = start_address;
	while(pc >= 0)	cycle();
}

void oisc::load_memory(width_t start_address, width_t end_address, width_t * data)
{
	std::memcpy(memory + (start_address * sizeof(width_t)), data, (end_address - start_address) * sizeof(data));
}

volatile width_t * oisc::get_memory()
{
	return memory;
}

width_t oisc::get_pc()
{
	return pc:
}

// interactive_oisc implementation
uint8_t interactive_oisc::get_input()
{
	std::string input;
	std::cin >> input;
	std::vector<string> * parsed_input = split_string(input);
	uint8_t num_args = parsed_input.length();

	if("print" == parsed_input[0])
	{
		switch(num_args)
		{
			case 1:
				return invalid_input("Too few arguments for command 'print'.");
			case 2:
				width_t location = std::stoi(parsed_input[1]);
				print_location(location, memory[location]);
				return 0;
			default:
				return invalid_input("Too many arguments for command 'print'.");
		}

	}
	else if("continue" == parsed_input[0])
	{
		switch(num_args)
		{
			case 1:
				num_steps = 1;
				return 0;
			default:
				return invalid_input("Too many arguments for command 'continue'.");
		}
	}
	else if("stop" == parsed_input[0] ||
					"halt" == parsed_input[0] ||
					"quit" == parsed_input[0] ||
					"exit" == parsed_input[0])
	{
		switch(num_args)
		{
			case 1:
				return -1;
			default:
				return invalid_input("Too many arguments for command '" + parsed_input[0] + "'.");
		}
	}
	else if("load" == parsed_input[0] ||
					"ld" == parsed_input[0])
	{
		//@TODO: Load some binary into memory
		return 0;
	}
	else if("set" == parsed_input[0])
	{
		switch(num_args)
		{
			case 1:
			case 2:
				return invalid_input("Too few arguments for command 'set'.");
			case 3:
				memory[parse_literal(parsed_input[1])] = memory[parse_literal(parsed_input[2])];
				return 0;
		}
	}
	else if("memdump" == parsed_input[0])
	{
		uint8_t num_locations = 8;
		width_t start_location = pc;

		switch(num_args)
		{
			case 1:
				break;
			case 3:
				start_location = std::stoi(parsed_input[2]);
			case 2:
				num_locations = parse_literal(parsed_input[1]);
				break;
			default:
				return invalid_input("Too many arguments for command 'memdump'.");
		}

		for(int i = 0; i < num_locations; i++)
			print_location(start_location + i, memory[start_location + i]);
		return 0;
	}
	else if("reset" == parsed_input[0])
	{
		switch(num_args)
		{
			case 1:
				zero_mem(memory);
				pc = 0;
				return 0;
			default:
				return invalid_input("Too many arguments for command 'reset'.");
		}
	}
	else if("import" == parsed_input[0])
	{
		//@TODO: Import some sort of file
		return 0;
	}
	else if("step" == parsed_input[0])
	{
		uint64_t num_steps = 1;
		switch(num_args)
		{
			case 1:
				break;
			case 2:
				num_steps = parse_literal(parsed_input[1]);
			default:
				return invalid_input("Too many arguments for command 'step'.");
		}
		return num_steps;
	}
	else if("subleq" == parsed_input[0])
	{
		width_t a,b;
		width_t c = pc + 3;
		switch(num_args)
		{
			case 1:
			case 2:
				return invalid_input("Too few arguments for command 'subleq'.");
			case 4:
				c = parse_literal(parsed_input[4]);
			case 3:
				a = parse_literal(parsed_input[2]);
				b = parse_literal(parsed_input[3]);
				break;
			default:
				return invalid_input("Too many arguments for command 'subleq'.");
		}
		memory[pc]     = a;
		memory[pc + 1] = b;
		memory[pc + 2] = c;
		return 1;
	}
	else
	{
		return invalid_input("Command not recognized.");
	}
}

void interactive_oisc::run(volatile uint8_t *continue_running, width_t start_address = 0)
{
	pc = start_address;
	uint64_t num_steps;

	while(*continue_running)
	{
		num_steps = get_input();
		while(num_steps > 0)
		{
			cycle();
			num_steps--;
		}
	}
}
