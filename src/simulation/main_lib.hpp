/*
* @file main_lib.hpp
* Helper functions for main
*
* @author:  Evan Lissoos
* @date Created:  8/14/17
*/

#include <iostream>
#include <string>
#include <thread>
#include "lib/interactive_oisc.h"
#include "lib/oisc.h"
#include "lib/mem_io.hpp"

using namespace std;

#define INTERACTIVE_MODE 1
#define FILENAME         string("out.bin")

/*
* run_oisc_thread
*
* description: Wrapper funcrion for running an oisc in a thread
* arguments  : o - oisc object to run
* returns    : None
*/
void run_oisc_thread(oisc * o)
{
	o->run();
}

/*
* run_interactive
*
* description: Interactive mode setup and run
* arguments  : None
* returns    : None
*/
void run_interactive()
{
	interactive_oisc * test_oisc = new interactive_oisc();
	test_oisc->run();
	delete test_oisc;
}

/*
* run_oisc
*
* description: Interactive mode setup and run
* arguments  : filename - file name of binary to load
* returns    : None
*/
void run_oisc(string filename)
{
	// Allocate and load binary
	oisc * test_oisc = new oisc();
	test_oisc->load_file(filename);

	// Start threads
	volatile width_t * mem = test_oisc->get_memory();
	thread sim_thread(run_oisc_thread, test_oisc);
	thread in_thread (input_thread, mem);
	thread out_thread(output_thred, mem);

	// Join and make sure terminal is reset to normal state
	out_thread.join();
	system("/bin/stty cooked");
}
