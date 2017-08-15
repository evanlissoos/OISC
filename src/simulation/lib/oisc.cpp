/*
* @file xc.cpp
* Implementation for OISC
*
* @author:  Evan Lissoos
* @date Created:  8/5/17
*/

#include "oisc.h"

/*
* oisc
*
* description: No argument constructor for oisc
* arguments  : None
* returns    : None
*/
oisc::oisc()
{
	// Allocate memory and mark as owner of memory
	pc = LOAD_ADDRESS;
	memory = new uwidth_t[MEM_SIZE];
	this->zero_mem();
	memory[NEG_ONE] = -1;
	memory[POS_ONE] = 1;
	memory_owner = true;
}

/*
* oisc
*
* description: Memory only constructor for oisc
* arguments  : mem - pointer to memory block
* returns    : None
*/
oisc::oisc(volatile uwidth_t * mem)
{
	// Copy memory pointer
	pc = LOAD_ADDRESS;
	memory = mem;
	memory_owner = false;
}

/*
* ~oisc
*
* description: Destructor for oisc
* arguments  : None
* returns    : None
*/
oisc::~oisc()
{
	// Only free memory if it was allocated by this object
	if(memory_owner)	delete memory;
}

/*
* get_memory
*
* description: Get memory pointer
* arguments  : None
* returns    : Pointer to memory block for this object
*/
volatile uwidth_t * oisc::get_memory()
{
	return memory;
}

/*
* get_pc
*
* description: Get PC value
* arguments  : None
* returns    : Value of PC
*/
uwidth_t oisc::get_pc()
{
	return pc;
}

/*
* run
*
* description: Enter OISC CPU running state
* arguments  : start_address (optional) - address to start execution (defaults to 3)
* returns    : None
*/
void oisc::run(uwidth_t start_address)
{
	// Halting condition is PC getting to 0
	// Since the first 3 memory addresses are 0, if PC reaches 0, it will stay there
	pc = start_address;
	while(pc > 0)	cycle();
}

/*
* load_memory
*
* description: Load memory with a block of data
* arguments  : start_address - address to start loading data
             : end_address   - last address to load data
* returns    : None
*/
void oisc::load_memory(uwidth_t start_address, uwidth_t end_address, uwidth_t * data)
{
	memcpy((void *) &(memory[start_address]), (void *) data, (end_address - start_address) * sizeof(data));
}

/*
* load_file
*
* description: Load memory with contents of a file
* arguments  : filename - name of file to load
* returns    : 1 on failure and 0 on success
*/
uint8_t oisc::load_file(string filename)
{
	// Open file and get length
	ifstream file_in(filename, ios::in | ios::binary);
	file_in.seekg(0, file_in.end);
	uwidth_t length = file_in.tellg();
	file_in.seekg(0, file_in.beg);

	// If the binary is too big to fit in memory, exit function
	if(length > MAX_PROGRAM_SIZE)
	{
		file_in.close();
		return 1;
	}

	// Read data into memory and close file
	file_in.read((char *) &(memory[LOAD_ADDRESS]), length);
	file_in.close();

	// Set PC to where file was loaded
	pc = LOAD_ADDRESS;
	return 0;
}

/*
* zero_mem
*
* description: Clear memory of this object
* arguments  : None
* returns    : None
*/
void oisc::zero_mem()
{
	memset((void*) memory, 0, MEM_SIZE * sizeof(uwidth_t));
}

/*
* cycle
*
* description: Simulation of a clock
* arguments  : None
* returns    : None
*/
void oisc::cycle()
{
	// Getting operands
	uwidth_t a, b, c;
	a = memory[pc];
	b = memory[pc + 1];
	c = memory[pc + 2];
	// Performing arithmatic step
	memory[b] = memory[b] - memory[a];
	// Performing branch step
	pc = ((int16_t) memory[b] > 0) ? pc + 3 : c;
}
