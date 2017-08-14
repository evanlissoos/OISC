WAIT_ON_KEY:
	subleq 0x0000,  FKEY, WAIT_ON_KEY ; Wait until key pressed
	mov    DKEY,    DDISP             ; Copy data from keyboard to display
	subleq NEG_ONE, FDISP             ; Set display flag
	subleq FKEY,    FKEY, WAIT_ON_KEY ; Clear keyboard flag and jump to waiting
