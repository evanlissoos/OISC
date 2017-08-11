/*
* @file xc.cpp
* Implementation for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#include "oisc.h"

#define PRINT_HEX "0x" << setfill('0') << setw(sizeof(width_t)*2) << hex

// Helpers
static void split_string(const string &input_string, vector<string> *vec)
{
	string str;
	for(uint32_t i = 0; i < input_string.length(); i++)
	{
		if(input_string[i] != ' ')
			str += input_string[i];
		else
		{
			vec->push_back(str);
			str = "";
		}
	}
	if(!str.empty())
		vec->push_back(str);
}

/*
static uint8_t is_in(string &value, vector<string> &list)
{
	// Ooo look at me I'm hot shit becasue I can interate
	for(auto it = list.begin(); it != list.end(); ++it)
		if(*it == value)	return true;
	return false;
}
*/

static void print_location(width_t location, width_t value)
{
	cout << PRINT_HEX << location << ": " << PRINT_HEX << value << endl;
}

static width_t parse_literal(string &literal)
{
	if(literal.find("0x") == 0 || literal.find("0X") == 0)
		return stoi(literal, 0, 16);
	else if(literal.find("0b") == 0 || literal.find("0B") == 0)
		return stoi(literal.substr(2), 0, 2);
	else if(literal.find("0h") == 0 || literal.find("0H") == 0)
		return stoi(literal.substr(2), 0, 8);
	else
		return stoi(literal);
}

static void zero_mem(volatile width_t * mem)
{
	memset((void*) mem, 0, MEM_SIZE * sizeof(width_t));
}

static uint8_t invalid_input(string error_msg)
{
	cout << "Invalid input: " << error_msg << endl;
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

oisc::oisc(volatile width_t * mem)
{
	pc = 0;
	memory = mem;
	memory_owner = false;
}

oisc::~oisc()
{
	if(memory_owner) free((void *) memory);
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

// interactive_oisc implementation
width_t interactive_oisc::get_input()
{
	string input;
	getline(cin, input);
	vector<string> * parsed_input = new vector<string>();
	split_string(input, parsed_input);
	uint8_t num_args = parsed_input->size();

	if(num_args == 0)
		return 0;
	else if(strcmp("print", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
				return invalid_input(string("Too few arguments for command 'print'."));
			case 2:
			{
				width_t location = stoi((*parsed_input)[1]);
				print_location(location, memory[location]);
				return 0;
			}
			default:
				return invalid_input(string("Too many arguments for command 'print'."));
		}

	}
	else if(strcmp("continue", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
				return 1;
			default:
				return invalid_input(string("Too many arguments for command 'continue'."));
		}
	}
	else if( strcmp("stop", (*parsed_input)[0].c_str()) == 0 ||
				strcmp("halt", (*parsed_input)[0].c_str()) == 0 ||
				strcmp("quit", (*parsed_input)[0].c_str()) == 0 ||
				strcmp("exit", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
				return -1;
			default:
				return invalid_input(string("Too many arguments for command '" )+ (*parsed_input)[0].c_str() + "'.");
		}
	}
	else if( strcmp("load", (*parsed_input)[0].c_str()) == 0 ||
				strcmp("ld", (*parsed_input)[0].c_str()) == 0)
	{
		//@TODO: Load some binary into memory
		switch(num_args)
		{
			case 1:
				return invalid_input(string("Too few arguments for command '"+ (*parsed_input)[0] +"'."));
			case 2:
			{
				ifstream file_in((*parsed_input)[1], ios::in | ios::binary);
				file_in.seekg(0, file_in.end);
				width_t length = file_in.tellg();
				file_in.seekg(0, file_in.beg);

				if(length > MAX_PROGRAM_SIZE)
				{
					file_in.close();
					return invalid_input(string("Too many arguments for command '"+ (*parsed_input)[0] +"'."));
				}

				file_in.read((char *) &(memory[LOAD_ADDRESS]), length);
				file_in.close();

				// Loading jump to start address at current PC location
				memory[pc]     = 0;
				memory[pc + 1] = 0;
				memory[pc + 2] = LOAD_ADDRESS;
				return 0;
			}
			default:
				return invalid_input(string("Too many arguments for command '"+ (*parsed_input)[0] +"'."));
		}
		return 0;
	}
	else if(strcmp("set", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
			case 2:
				return invalid_input(string("Too few arguments for command 'set'."));
			case 3:
				memory[parse_literal((*parsed_input)[1])] = parse_literal((*parsed_input)[2]);
				return 0;
		}
	}
	else if(strcmp("memdump", (*parsed_input)[0].c_str()) == 0)
	{
		uint8_t num_locations = 8;
		width_t start_location = pc;

		switch(num_args)
		{
			case 1:
				break;
			case 3:
				start_location = stoi((*parsed_input)[2]);
			case 2:
				num_locations = parse_literal((*parsed_input)[1]);
				break;
			default:
				return invalid_input(string("Too many arguments for command 'memdump'."));
		}

		for(int i = 0; i < num_locations; i++)
			print_location(start_location + i, memory[start_location + i]);
		return 0;
	}
	else if(strcmp("reset", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
				zero_mem(memory);
				pc = 0;
				return 0;
			default:
				return invalid_input(string("Too many arguments for command 'reset'."));
		}
	}
	else if(strcmp("import", (*parsed_input)[0].c_str()) == 0)
	{
		//@TODO: Import some sort of file
		return 0;
	}
	else if(strcmp("step", (*parsed_input)[0].c_str()) == 0)
	{
		switch(num_args)
		{
			case 1:
				return 1;
			case 2:
				return parse_literal((*parsed_input)[1]);
			default:
				return invalid_input(string("Too many arguments for command 'step'."));
		}
	}
	return invalid_input(string("Command not recognized."));
}

void interactive_oisc::run(volatile uint8_t *continue_running, width_t start_address)
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

void interactive_oisc::run(width_t start_address)
{
	pc = start_address;
	uint64_t num_steps;
	uint8_t have_printed = false;

	while(true)
	{
		if(!have_printed)
		{
			cout << "PC: " << PRINT_HEX << pc << endl << "Memory: " << endl;
			for(int i = 0; i < 8; i++)
				print_location(pc + i, memory[pc + i]);
			have_printed = true;
		}
		num_steps = get_input();
		if(num_steps == (width_t) -1)	return;
		while(num_steps > 0)
		{
			cycle();
			num_steps--;
			have_printed = false;
		}
	}
}
