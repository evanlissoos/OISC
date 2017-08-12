from re import findall
from metadata import *

# Called on label pass
def parse_labels(line):
	# Check if empty line
    if line.split() is '':
        return

    # Ignoring comments
    line = (line.split(';'))[0]

	# Parse label
    label_split = line.split(':')
    if len(label_split) is not 1:
        new_label = label_split[0].strip()
        if new_label in meta.labels:
            error("Redefinition of label '"+ new_label +"' line: " + str(meta.line_number))
        meta.labels[new_label] = meta.cur_address
        # If there is no instruction on this line, finish parsing
        if label_split[1].strip() is '':
            return
        line = label_split[1]

	# Calculating address
    for key in meta.supported_ops:
        if key in line:
            meta.cur_address += meta.supported_ops[key].total_mem

# Called on compiling pass
def parse_line(line):
    # Check if empty line
    if line.split() is '':
        return None

    # Ignoring comments
    line = (line.split(';'))[0]

    # Checking for labels
    label_split = line.split(':')
    if len(label_split) is not 1:
        # If there is no instruction on this line, finish parsing
        if label_split[1].strip() is '':
            return None
        line = label_split[1]
    # Split on whitespace
    return findall(r"[\w']+", line)

#https://stackoverflow.com/questions/34057237/can-i-use-binary-to-write-integer-constants-in-assembly
def parse_literal(literal):
    if literal[0].isalpha():
        try:
            return meta.labels[literal]
        except KeyError:
            error("Invalid '" + literal + "' line: " + str(meta.line_number))

    original_lit = literal
    def test_literal(base):
        try:
            ret_val = int(literal, base)
            if (ret_val > cpu.max_val()) or (ret_val < cpu.min_val()):
                error("Invalid literal (out of exceptable bounds for given bit width) '"+ original_lit + "' line: " + str(meta.line_number))
            return ret_val

        except ValueError:
            error("Invalid literal '"+ original_lit + "' line: " + str(meta.line_number))

    # Hex
    if   literal.startswith('0x') or literal.startswith('0h') or literal.startswith('$0') or literal.endswith('h'):
        literal = literal.replace('0x', '')
        literal = literal.replace('0h', '')
        literal = literal.replace('$0', '')
        literal = literal.replace('h',  '')
        return test_literal(16)

    # Octal
    elif literal.startswith('0o') or literal.startswith('0q') or literal.endswith('o') or literal.endswith('q'):
        literal = literal.replace('0o', '')
        literal = literal.replace('0q', '')
        literal = literal.replace('o',  '')
        literal = literal.replace('q',  '')
        return test_literal(8)

    # Binary
    elif literal.startswith('0b') or literal.startswith('0y') or literal.endswith('b') or literal.endswith('y'):
        literal = literal.replace('_',  '')
        literal = literal.replace('0b', '')
        literal = literal.replace('0y', '')
        literal = literal.replace('b',  '')
        literal = literal.replace('y',  '')
        return test_literal(2)

    # Decimal
    literal = literal.replace('d',  '')
    return test_literal(10)
