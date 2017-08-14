/*
* @file xc.cpp
* Implementation for Interactive OISC
*
* @author:  Evan Lissoos
* @date Created:  8/11/17
*/

#include "interactive_oisc.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

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

static uint8_t invalid_input(string error_msg)
{
	cout << "Invalid input: " << error_msg << endl;
	return 0;
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
				// Load binary into memory
				if(this->load_file((*parsed_input)[1])) return invalid_input(string("Invalid file input."));
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
				this->zero_mem();
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
	else if(strcmp("step", (*parsed_input)[0].c_str()) == 0 ||
					strcmp("s", (*parsed_input)[0].c_str()) == 0)
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
