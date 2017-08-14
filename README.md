# OISC - One Instruction Set Computer

## Overview:
This may be the world's shittiest CPU, but I guess this proves that any CPU, no matter how simple, can do anything.

## Background
I found out that it's possible to make a Turing Complete ISA with one instruction and apparently I have nothing better to do other than play Overwatch and eat ramen so here I am.

## The Instruction
The instruction implemented is `subleq` which is shorthand for subtract and branch if less than or equal to zero. There are two different syntaxes for the instruction: 3 argument and 2 argument.
* 3 Argument:
```assembly
subleq a, b, c    ; Mem[b] = Mem[b] - Mem[a]
                  ; if (Mem[b] ≤ 0) goto c
```
* 2 Argument:
```assembly
subleq a, b	  ; Mem[b] = Mem[b] - Mem[a]
                  ; goto PC + 3
```

## How To Use
1. To start off, you'll need to initialize the program. Run: `sh oisc.sh init`.
2. Boom, set up is done. Now you can run do whatever you want. Run `sh oisc.sh asm IN_FILENAME [OUT_FILENAME]` to assemble an assembly file. `IN_FILENAME` is the assembly file you input and `OUT_FILENAME` is the _optional_ binary output name. Default is out.bin.
3. Run `sh oisc.sh sim` to run the interactive simulator. By default, the simulator runs in interactive mode.
4. To try out a demo of memory mapped IO, assemble the `test/io_test.asm` file, change the `#define INTERACTIVE_MODE` to zero, run `sh oisc.sh init` and then run the simulator!

## Assembly Syntax
### Instructions:
  For the native instruction set, there are the variations of the instruction supported: two and three argument as seen in **The Instruction** section.  

```assembly
subleq 0, 1, 3
subleq 0, 1
```

There are currently more instructions being implemented! They aren't actually different instructions, just macros that get converted into `subleq`. Check out `src/assembler/lib/instructions.py` for more details :)

### Data
  Raw data can be placed in the code using the fake op-code `data` or `.data`. The data can be accessed using labels.

```assembly
data 8
.data 3
```

### Labels
  Labels are supported in this shitty assembly language! Just use them as you know how; on the same line or on the line before the instruction/data.

```assembly
subleq A, B

A:
data 8
B: data 3
```

### Literals
  If you're a fan of decimal, binary, or even hex, we got you covered. Oh, you're a strange fella that uses octal? We even support that!  
  * For hex, you can use prefixes: `0x`, `0h`, `$0` or suffix `h`
  * For binary, prefixes: `0b`, `0y` or suffixes `b`, `y`
  * For octal, prefixes `0o`, `0q` or suffixes `o`, `q`
  * For decimal, no prefix or suffix `d` if you're weird and want to be explicit

```assembly
subleq 0x2, 1001010b, A

A:
data 0o345
```

### Comments
  Comments are supported using a `;`.  

```assembly
A:
subleq 0, 0     ; MEM[0] = 0
subleq 0, 0, A  ; JMP A
```


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
	¯\\\_(ツ)\_/¯
* Verilog implementation:  
	What happens when you throw HDL on top of this? I'm not sure I really want to find out...
* Burn it all to the ground:  
	:fire::fire::fire:

## FAQ
##### Why did you use C++?
Pointers are ~~a fucking bitch to debug~~ really fun.
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

## Current to-do list:
* Support for labels in the assembler (and maybe offsets)
* Support for more complex instructions
