# -*- coding: utf-8 -*-
from lib.metadata import *
from lib.parse import *

# m[op2] = m[op2] - m[op1]
# if (m[op2] ≤ 0) pc = c
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
			meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		else:
			meta.data_array.append(parse_literal(line_data[3]))

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
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Second instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)

# m[op] = m[op] + 1
class inc():
	#Instruction data
	def __init__(self):
		self.min_operands = 1
		self.max_operands = 1
		self.total_mem	= 3

	# Parse function
	def parse_op(self, line_data):
		meta.data_array.append(0x35)
		meta.data_array.append(parse_literal(line_data[1]))
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)

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
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)

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
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Second instruction
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Third instruction
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Fourth instruction
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)

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

# m[b] = m[a] * m[b]
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
		total = len(meta.data_array) + cpu.start_location + 1
		# First instruction (data/nop)
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		# Second instruction (inc)
		meta.data_array.append(0x35)
		meta.data_array.append(op2)
		top = len(meta.data_array) + cpu.start_location + 1
		meta.data_array.append(top)
		# Third instruction (subleq)
		meta.data_array.append(0x36)
		meta.data_array.append(op2)
		meta.data_array.append(top+12)
		# Fourth instruction (add)
		meta.data_array.append(op1)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		meta.data_array.append(0)
		meta.data_array.append(total)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(top)
		# Fifth instruction (add)
		meta.data_array.append(total)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		meta.data_array.append(0)
		meta.data_array.append(op2)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
		meta.data_array.append(0)
		meta.data_array.append(0)
		meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)

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

meta.supported_ops = {'subleq': subleq(), 'jmp':jmp(), 'mov':mov(), 'data': data(), 'add': add(), 'inc': inc(), 'sub':sub(), 'mul':mul(), 'halt': halt()}
