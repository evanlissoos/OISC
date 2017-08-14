WAIT_ON_KEY:
	subleq 0x0000, 0x0030, WAIT_ON_KEY ; Wait until key pressed
	mov    0x0031, 0x0041              ; Copy data from keyboard to display
	subleq   NEG1, 0x0040              ; Set display flag
	subleq 0x0030, 0x0030, WAIT_ON_KEY ; Clear keyboard flag and jump to waiting

NEG1:
	.data  0xFFFF
