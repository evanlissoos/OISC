#include "lib/interactive_oisc.h"
#include "lib/oisc.h"
#include "lib/mem_io.hpp"
#include <iostream>
#include <string>
#include <thread>

#define INTERACTIVE_MODE 1

using namespace std;

static void run_interactive()
{
	interactive_oisc * test_oisc = new interactive_oisc();
	test_oisc->run();
	delete test_oisc;
}

static void run_oisc_thread(oisc * o)
{
	o->run();
}


static void run_oisc(string filename)
{
	oisc * test_oisc = new oisc();
	test_oisc->load_file(filename);

	// Start threads
	volatile width_t * mem = test_oisc->get_memory();
	thread sim_thread(run_oisc_thread, test_oisc);
	thread in_thread (input_thread, mem);
	thread out_thread(output_thred, mem);

	sim_thread.join();
	system("/bin/stty cooked");
}


int main()
{
#if INTERACTIVE_MODE
	run_interactive();
#else
	run_oisc(string("out.bin"));
#endif
	return 0;
}
