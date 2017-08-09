import re

# @TODO: Support for additional ops and support for labels and macros?

supported_ops = {'subleq': subleq()}
bit_width = 16
max_val = (1 << bit_width) - 1
min_val = (1 << (bit_width-1)) * -1

in_filename  = ''
out_filename = ''
data_array = []
line_number = 0


def error(err_message):
    print('\033[91m\033[1mERROR:\033[0m ' + err_message)
    quit()

#https://stackoverflow.com/questions/34057237/can-i-use-binary-to-write-integer-constants-in-assembly
def parse_literal(literal):
    ret_val = None
    original_lit = literal

    def test_literal(base):
        try:
            ret_val = int(literal, base)
            if (ret_val > max_val) or (ret_val < min_val):
                error("Invalid literal (out of exceptable bounds for given bit width) '"+ original_lit + "' line: " + str(line_number))
        except ValueError:
            error("Invalid literal '"+ original_lit + "' line: " + str(line_number))

    # Hex
    if   literal.startswith('0x') or literal.startswith('0h') or literal.startswith('$0') or literal.endswith('h'):
        literal = literal.replace('0x', '')
        literal = literal.replace('0h', '')
        literal = literal.replace('$0', '')
        literal = literal.replace('h',  '')
        test_literal(16)

    # Octal
    elif literal.startswith('0o') or literal.startswith('0q') or literal.endswith('o') or literal.endswith('q'):
        literal = literal.replace('0o', '')
        literal = literal.replace('0q', '')
        literal = literal.replace('o',  '')
        literal = literal.replace('q',  '')
        test_literal(8)

    # Binary
    elif literal.startswith('0b') or literal.startswith('0y') or literal.endswith('b') or literal.endswith('y'):
        literal = literal.replace('_',  '')
        literal = literal.replace('0b', '')
        literal = literal.replace('0y', '')
        literal = literal.replace('b',  '')
        literal = literal.replace('y',  '')
        test_literal(2)

    # Decimal
    else:
        literal = literal.replace('d',  '')
        test_literal(10)

    return ret_val

class subleq(op):
    min_operands = 2
    max_operands = 3

    def __init__(self):
        self.min_operands
        self.max_operands

    def parse_op(line_data):
        data_array.append(parse_literal(line_data[1]))
        data_array.append(parse_literal(line_data[2]))
        num_ops = len(line_data) - 1
        if num_ops is 2:
            data_array.append(len(data_array) + 1)
        else:
            data_array.append(parse_literal(line_data[3]))

with open(in_filename, 'r') as in_f:
    for line in in_f:
        line_data = re.findall(r"[\w']+", line)
        num_operands = len(line_data) - 1

        # Opcode parsing
        curr_op = None
        try:
            curr_op = supported_ops[line_data[0]]
        except KeyError:
            error("Invalid opcode '"+ line_data[0] +"' line: " + str(line_number))
        if (curr_op.min_operands > num_operands) or (curr_op.max_operands < num_operands):
            error("Invalid number of operands for opcode: '"+ line_data[index] + "' line: " + str(line_number))

        curr_op.parse_op(line_data)
        line_number += 1

binary_data = []
for data in data_array:
    iteratons = bit_width / 8
    # Get rid of this reversed statement to change endianness of file
    for i in reversed(range(iteratons)):
        binary_data.append((data >> (i * 8)) & 0xFF)