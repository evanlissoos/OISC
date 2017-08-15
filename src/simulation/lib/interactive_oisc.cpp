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

#define PRINT_HEX "0x" << setfill('0') << setw(sizeof(uwidth_t)*2) << hex

/*
* zero_mem
*
* description: Helper that splits string on whitespace
* arguments  : input_string - string to operate on
             : vec          - vector to place components in
* returns    : None
*/
static void split_string(const string &input_string, vector<string> *vec)
{
	string str;
	for(uint32_t i = 0; i < input_string.length(); i++)
	{
		// If not a space, add charachter to string
		if(input_string[i] != ' ')
			str += input_string[i];
		// If space found, push the word to the vector
		else
		{
			vec->push_back(str);
			str = "";
		}
	}
	// If the last string isn't empty, push it to the vector
	if(!str.empty())
		vec->push_back(str);
}

/*
* print_location
*
* description: Helper that prints formatted memory location and value
* arguments  : location - memory location to print
             : value    - memory contents to print
* returns    : None
*/
static void print_location(uwidth_t location, uwidth_t value)
{
	cout << PRINT_HEX << location << ": " << PRINT_HEX << value << endl;
}

/*
* parse_literal
*
* description: Helper that converts a string into a uwidth_t
* arguments  : literal - string to convert
* returns    : uwidth_t representation of literal
*/
static uwidth_t parse_literal(string &literal)
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

/*
* invalid_input
*
* description: Helper that prints error messages
* arguments  : error_msg - error message to be printed
* returns    : uwidth_t representation of literal
*/
static uint8_t invalid_input(string error_msg)
{
	cerr << "Invalid input: " << error_msg << endl;
	return 0;
}

/*
* get_input
*
* description: Handles user input for interactive mode
* arguments  : None
* returns    : The number of cycles that should be run
*/
uwidth_t interactive_oisc::get_input()
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
				uwidth_t location = stoi((*parsed_input)[1]);
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
		uwidth_t start_location = pc;

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
				pc = LOAD_ADDRESS;
				memory[NEG_ONE] = 0xFFFF;
				memory[POS_ONE] = 1;
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

/*
* run
*
* description: Override running loop for interactive_oisc (two args)
* arguments  : continue_running         - pointer to variable that says if the oisc should continue running
               start_address (optional) - address to start excecution (defaults to 3)
* returns    : None
*/
void interactive_oisc::run(volatile uint8_t *continue_running, uwidth_t start_address)
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

/*
* run
*
* description: Override running loop for interactive_oisc (one arg)
* arguments  : start_address (optional) - address to start excecution (defaults to 3)
* returns    : None
*/
void interactive_oisc::run(uwidth_t start_address)
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
		if(num_steps == (uwidth_t) -1)	return;
		while(num_steps > 0)
		{
			cycle();
			num_steps--;
			have_printed = false;
		}
	}
}
