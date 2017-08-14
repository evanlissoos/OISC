# CPU Info
class cpu_info():
	def __init__(self, s_l, b_w):
		self.start_location = s_l
		self.bit_width	    = b_w
	def max_val(self):
		return (1 << self.bit_width) - 1
	def min_val(self):
		return (1 << (self.bit_width-1)) * -1

# Metadata required by classes and functions
class metadata():
	def __init__(self, s_l):
		self.labels			  = {'__start__': s_l, 'NEG_ONE': 0x35, 'POS_ONE': 0x36, 'ZERO': 0, 'Z': 0, 'FKEY': 0x30, 'DKEY': 0x31, 'FDISP': 0x40, 'DDISP': 0x41}
		self.cur_address		 = s_l
		self.line_number		 = 1
		self.supported_ops	     = {}
		self.data_array		     = []

# Functions required by all files
def error(err_message):
	print('\033[91m\033[1mERROR:\033[0m ' + err_message)
	quit()

# Structures used for global tracking
s_l = 0x42
b_w = 16
cpu = cpu_info(s_l, b_w)
meta = metadata(s_l)
