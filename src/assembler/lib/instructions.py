from metadata import *
from parse import *

class subleq():
    #Instruction data
    def __init__(self):
        self.min_operands = 2
        self.max_operands = 3
        self.total_mem    = 3

    # Parse function
    def parse_op(self, line_data):
        num_ops = len(line_data) - 1
        meta.data_array.append(parse_literal(line_data[1]))
        meta.data_array.append(parse_literal(line_data[2]))
        if num_ops is 2:
            meta.data_array.append(len(meta.data_array) + cpu.start_location + 1)
        else:
            meta.data_array.append(parse_literal(line_data[3]))
        meta.cur_address += self.total_mem


class data():
    # Instruction data
    def __init__(self):
        self.min_operands = 1
        self.max_operands = 1
        self.total_mem    = 1

    # Parse function
    def parse_op(self, line_data):
        num_ops = len(line_data) - 1
        meta.data_array.append(parse_literal(line_data[1]))
        meta.cur_address += self.total_mem


meta.supported_ops = {'subleq': subleq(), 'data': data()}
