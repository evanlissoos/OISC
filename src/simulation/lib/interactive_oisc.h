/*
* @file interactive_oisc.h
* Header file for Interactive OISC
*
* @author:  Evan Lissoos
* @date Created:  8/11/17
*/

#ifndef INTERACTIVE_OISC_H
#define INTERACTIVE_OISC_H

#include "oisc.h"

class interactive_oisc: public oisc
{
	// Interactive functions
	public:
		void run(volatile uint8_t *continue_running, uwidth_t start_address = LOAD_ADDRESS);
		void run(uwidth_t start_address = LOAD_ADDRESS);
	private:
		uwidth_t get_input();
};

#endif //INTERACTIVE_OISC_H
