# -*- coding: utf-8 -*-
from lib.metadata import *
from lib.parse import *

# Helper for getting next memory location
def next():
	return len(meta.data_array) + cpu.start_location + 1

##############
### SUBLEQ ###
##############

# m[op2] = m[op2] - m[op1]
# if (m[op2] ≤ 0) pc = op3
class subleq():
	#Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 3
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(parse_literal(line_data[1]))
		meta.data_array.append(parse_literal(line_data[2]))
		if (len(line_data) - 1) is 2:
			meta.data_array.append(next())
		else:
			meta.data_array.append(parse_literal(line_data[3]))

#######################
### PROGRAM CONTROL ###
#######################

# pc = op
class jmp():
	# Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		# First instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(parse_literal(line_data[1]))

class halt():
	# Instruction data
	def __init__(self):
		self.min_operands = 0
		self.max_operands = 0
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(0)

#################
### DATA FLOW ###
#################

# m[addr] = op
class data():
	# Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 1

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(parse_literal(line_data[1]))

# m[op2] = m[op1]
class mov():
	# Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem	= 12

	# Parse function
	def parse_op(self, line_data):
		op1 = parse_literal(line_data[1])
		op2 = parse_literal(line_data[2])
		# First instruction
		meta.data_array.append(op2)
		meta.data_array.append(op2)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(next())
		# Fourth instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())

###########
### I/O ###
###########

# m[op] = keyboard
class getc():
	# Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 15

	def parse_op(self, line_data):
		op = parse_literal(line_data[1])
		wait = next() - 3
		meta.data_array.append(0)
		meta.data_array.append(0x5)
		meta.data_array.append(wait)

		meta.data_array.append(op)
		meta.data_array.append(op)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(0x6)
		meta.data_array.append(wait)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(wait)
		meta.data_array.append(op)
		meta.data_array.append(next())

		meta.data_array.append(0x5)
		meta.data_array.append(0x5)
		meta.data_array.append(next())

# display = m[op]
class putc():
	# Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 15

	def parse_op(self, line_data):
		op = parse_literal(line_data[1])

		meta.data_array.append(0x8)
		meta.data_array.append(0x8)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(op)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(0x8)
		meta.data_array.append(next())
		# Fourth instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())

		meta.data_array.append(0x3)
		meta.data_array.append(0x7)
		meta.data_array.append(next())

#############
### LOGIC ###
#############
# M[A] = M[A] << M[B]
# NOTE: Clears M[B]
class bit_shift_left():
	# Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem    = 18

	# Parse function
	def parse_op(self, line_data):
		op1 = parse_literal(line_data[1])
		op2 = parse_literal(line_data[2])
		# First instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		top = next()
		done = top + 12
		meta.data_array.append(done + 3)
		# Second instruction (ADD)
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next())

		meta.data_array.append(0)
		meta.data_array.append(op1)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0x4)
		meta.data_array.append(op2)
		meta.data_array.append(done)
		# Fourth instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(top)
		# Fifth instruction DONE
		meta.data_array.append(0)
		meta.data_array.append(0)
		end = next()
		meta.data_array.append(end)

# M[A] = ~M[A]
class bit_not():
	# Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem    = 21

	# Parse function
	def parse_op(self, line_data):
		op = parse_literal(line_data[1])
		# First instruction (flip)
		meta.data_array.append(op)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Second instruction (sub 1)
		meta.data_array.append(0x4)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Third instruction (clear op)
		meta.data_array.append(op)
		meta.data_array.append(op)
		meta.data_array.append(next())
		# Fourth instruction (transfer part 1)
		meta.data_array.append(0)
		meta.data_array.append(1)
		meta.data_array.append(next())
		# Fifth instruction (transfer part 2)
		meta.data_array.append(1)
		meta.data_array.append(op)
		meta.data_array.append(next())
		# Sixth instruction (reset M[0])
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Seventh instruction (reset M[1])
		meta.data_array.append(1)
		meta.data_array.append(1)
		meta.data_array.append(next())

##################
### ARITHMETIC ###
##################

# m[op2] = m[op2] + m[op1]
class add():
	#Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem	= 9

	# Parse function
	def parse_op(self, line_data):
		op1 = parse_literal(line_data[1])
		op2 = parse_literal(line_data[2])
		# First instruction
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())

# m[op2] = m[op2] - m[op1]
class sub():
	#Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(parse_literal(line_data[1]))
		meta.data_array.append(parse_literal(line_data[2]))
		meta.data_array.append(next())

# m[op2] = m[op1] * m[op2]
# UNSIGNED
class mul():
	# Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem	= 27

	# Parse function
	def parse_op(self, line_data):
		op1 = parse_literal(line_data[1])
		op2 = parse_literal(line_data[2])
		total = next()
		# First instruction (data/nop)
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Second instruction (inc)
		meta.data_array.append(0x3)
		meta.data_array.append(op2)
		top = next()
		meta.data_array.append(top)
		# Third instruction (subleq)
		meta.data_array.append(0x4)
		meta.data_array.append(op2)
		meta.data_array.append(top+12)
		# Fourth instruction (add)
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next())
		meta.data_array.append(0)
		meta.data_array.append(total)
		meta.data_array.append(next())
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(top)
		# Fifth instruction (add)
		meta.data_array.append(total)
		meta.data_array.append(0)
		meta.data_array.append(next())
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(next())
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())

# m[op1] = m[op2] / m[op1]
# m[op2] = m[op2] % m[op1]
# UNSIGNED
class div():
	# Instruction data
	def __init__(self):
		self.min_operands = 2
		self.max_operands = 2
		self.total_mem	= 51

	# Parse function
	def parse_op(self, line_data):
		op1 = parse_literal(line_data[1])
		op2 = parse_literal(line_data[2])
		###
		quotient = next() -1
		temp_z = quotient + 1
		meta.data_array.append(0)
		meta.data_array.append(0)
		second_z_check = next()
		meta.data_array.append(second_z_check + 12)
		###SECOND_Z_CHECK
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next() + 42)
		#
		meta.data_array.append(0)
		meta.data_array.append(0)
		rem_zero = next()
		meta.data_array.append(rem_zero + 9)
		###REM_ZERO
		meta.data_array.append(0x3)
		meta.data_array.append(quotient)
		meta.data_array.append(next())
		#
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next() + 24)
		###FIRST_Z_CHECK
		meta.data_array.append(0)
		meta.data_array.append(op1)
		top = next()
		meta.data_array.append(second_z_check)
		###
		meta.data_array.append(op1)
		meta.data_array.append(op2)
		meta.data_array.append(next() + 6)
		###
		meta.data_array.append(0x3)
		meta.data_array.append(quotient)
		meta.data_array.append(next())
		###
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(top)
		### DONE
		meta.data_array.append(op2)
		meta.data_array.append(temp_z)
		meta.data_array.append(rem_zero)
		### ADD
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		mov_a = next()
		meta.data_array.append(mov_a)
		###MOV
		meta.data_array.append(op1)
		meta.data_array.append(op1)
		meta.data_array.append(next())
		# Second instruction
		meta.data_array.append(quotient)
		meta.data_array.append(0)
		meta.data_array.append(next())
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(op1)
		meta.data_array.append(next())
		# Fourth instruction END
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(next())

# m[op] = m[op] + 1
class inc():
	#Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(0x3)
		meta.data_array.append(parse_literal(line_data[1]))
		meta.data_array.append(next())

# m[op] = m[op] - 1
class dec():
	#Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(0x4)
		meta.data_array.append(parse_literal(line_data[1]))
		meta.data_array.append(next())

meta.supported_ops = {'subleq': subleq(), 'jmp':jmp(), 'mov':mov(), 'data': data(), 'add': add(), 'inc': inc(), 'sub':sub(), 'mul':mul(), 'div':div(), 'halt': halt(), 'not': bit_not(), 'shl':bit_shift_left()}
