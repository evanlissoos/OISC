# OISC - One Instruction Set Computer

## Overview:
This may be the world's shittiest CPU, but I guess this proves that any CPU, no matter how simple, can do anything.

## Background
I found out that it's possible to make a Turing Complete ISA with one instruction and apparently I have nothing better to do other than play Overwatch and eat ramen so here I am.

## Goals
In life? None. But I'm assuming you mean this project, Mr. Big Text Man.
The initial plan is to make a basic simulation of the ISA. From there, there's a lot I'd like to do with this:
* Memory mapped IO:  
    Have a thread monitor some memory locations of the simulation and handle them as IO.
* Massively parallel simulation:  
    Using a shared memory space, it'd be interesting to combine a bunch of these shitty little cores (possibly with GPU acceleration).
* Parser:  
    Write a basic parser so whatever sad sons of bitches try to use this can code _somewhat_ easily.
* Other ISA complience:  
    Building off the parser, implement other ISAs using this steaming pile of shit.
* LLVM Backend:  
    ¯\_(ツ)_/¯
* Verilog implementation:  
    What happens when you throw HDL on top of this? I'm not sure I really want to find out...
* Burn it all to the ground:
    :fire:

## FAQ
##### Why did you use C++?
Pointers are a ~~fucking bitch to debug~~ hoot.
##### Can I use this thing for another thing I wanna do?
Go for it.
##### Are you stupid?
Yes.
##### Why are you doing this?
Don't ask that question.
##### Does this have any use?
Okay, enough questions.


## Disclaimer:
I am not responsible for any negative side effects caused by looking through this project.
Symptoms may include but are not limited to: depression, shortness of breath, nausea, abdominal pain, diarrhea, swelling, and death.  

Please take OISC responsibly.

Please save me, this is not a joke. I am actually dying inside.
