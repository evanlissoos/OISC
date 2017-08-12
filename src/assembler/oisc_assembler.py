from __future__ import print_function
from argparse import *
from oisc_lib import *

# Argument parsing
parser = ArgumentParser()
parser.add_argument('-i', '--in_filename', help="Input file", metavar='IN')
parser.add_argument('-o', '--out_filename', help="Output file", default='out.bin', metavar='OUT')
args = parser.parse_args()
in_filename  = args.in_filename
out_filename = args.out_filename

with open(in_filename, 'r') as in_file:
    label_pass(in_file)
    binary_pass(in_file)

binary_output(out_filename)
