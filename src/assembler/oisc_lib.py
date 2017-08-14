from lib.parse import *
from lib.metadata import *
from lib.instructions import *

# Pass of source that collects data on labels
def label_pass(in_file):
	in_file.seek(0)
	for line in in_file:
		parse_labels(line)

# Pass of source that raw source representation
def binary_pass(in_file):
	in_file.seek(0)
	# Binary creation pass
	for line in in_file:
		line_data = parse_line(line)
		if line_data is None or not line_data:
			meta.line_number += 1
			continue
		num_operands = len(line_data) - 1

		# Opcode parsing
		curr_op = None
		try:
			curr_op = meta.supported_ops[line_data[0]]
		except KeyError:
			error("Invalid opcode '"+ line_data[0] +"' line: " + str(meta.line_number))
		if (curr_op.min_operands > num_operands) or (curr_op.max_operands < num_operands):
			error("Invalid number of operands for opcode: '"+ line_data[0] + "' line: " + str(meta.line_number))

		curr_op.parse_op(line_data)
		meta.line_number += 1

# Conversion of raw data to binary file
def binary_output(out_filename):
	binary_data = []
	for data in meta.data_array:
		iteratons = int(cpu.bit_width / 8)
		# Add reversed statment around range to change endianness
		for i in (range(iteratons)):
			binary_data.append((data >> (i * 8)) & 0xFF)

	with open(out_filename, 'wb') as out_f:
		out_f.write(bytearray(binary_data))
