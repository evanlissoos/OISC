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
		void run(volatile uint8_t *continue_running, width_t start_address = 0);
		void run(width_t start_address = 0);
	private:
		width_t get_input();
};

#endif //INTERACTIVE_OISC_H
