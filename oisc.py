from __future__ import print_function

# SIMULATION VARIABLES
# RAM
mem = [0] * 65536
# Program Counter
pc = 0
# Registers
a,b,c = 0,0,0

# Other variables
continue_count = 0


def parse_file(filename):
    with open(filename, 'r') as f:
        for line in f:
            line_data = line.lower().split()


def print_info(size):
    print('\nPC: 0x' + format(pc, '04X') + '\nMemory dump:')
    for i in range(size):
        print('0x' + format(pc + i, '04X') + ': ' + '0x' + format(mem[pc + i], '04X'))

def invalid_input():
    print('Error: Invalid input.')
    get_user_input()

#def load_binary(filename):

def check_array(list, value):
    try:
        return list.index(value)
    except ValueError:
        return -1

def get_user_input(func_input=''):
    raw_user_input = func_input
    if not raw_user_input:
        raw_user_input = raw_input()
    user_input = raw_user_input.split(' ')

    if 'print' in user_input:
        print(mem[int(user_input[1])])
        return 0
    elif ('continue' in user_input) or ('c' in user_input):
        return 1
    elif ('stop' in user_input) or ('halt' in user_input) or ('quit' in user_input) or ('exit' in user_input):
        print('Bye.')
        quit()
    elif ('load' in user_input) or ('ld' in user_input):
        print('Not implemented yet')
        return 0
    elif 'set' in user_input:
        mem[int(user_input[1])] = int(user_input[2])
        return 0
    elif 'memdump' in user_input:
        size = 8
        try:
            size = int(user_input[1])
        except IndexError:
            pass
        print_info(size)
        return 0
    elif 'reset' in user_input:
        for i in range(len(mem)):
            mem[i] = 0
        pc = 0
        a,b,c = 0,0,0
        return 0
    elif 'import' in user_input:
        with open(user_input[1], 'r') as f:
            for line in f:
                print(line)
                get_user_input(line)
        return 0
    elif ('step' in user_input) or ('s' in user_input):
        continue_count = int(user_input[1])
        return 1
    elif 'subleq' in user_input:
        arg3 = pc + 3
        try:
            arg3 = user_input[4]
        except IndexError:
            pass
        mem[pc]   = user_input[3].replace(',')
        mem[pc+1] = user_input[3]
        mem[pc+2] = arg3
        return 1
    else:
        invalid_input()
        return 0

def input_handler():
    while not get_user_input():
        pass

while pc >= 0:
    if not continue_count:
        print_info(8)
        input_handler()
    else:
        continue_count -= 1

    a = mem[pc]
    b = mem[pc+1]
    c = mem[pc+2]
    mem[b] = mem[b] - mem[a]
    if mem[b] > 0:
        pc += 3
    else:
        pc = c
