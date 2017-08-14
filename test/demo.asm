; demo.asm
; Created on 8/14/17 by Evan Lissoos
;
; This is a test program that shows off the IO capabilities of the CPU
;   as well as demonstate some of the higher order instructionsa that
;   are able to be synthasized using subleq and the assembler.
; NOTE: This is very basic and can only print single digit answers

WAIT_ON_KEY_A:
	subleq 0, FKEY, WAIT_ON_KEY_A      ; Wait until key pressed
  sub    ASCII_OFFSET, DKEY          ; Subtracting offset
	add    DKEY, A                     ; Copy data from keyboard to first arg
  subleq FKEY, FKEY                  ; Clear flag
WAIT_ON_KEY_B:
	subleq 0, FKEY, WAIT_ON_KEY_B      ; Wait until key pressed
  sub    ASCII_OFFSET, DKEY          ; Subtracting offset
  add    DKEY, B                     ; Copy data from keyboard to second arg
  subleq FKEY, FKEY                  ; Clear flag

  mul    A, B                        ; Multiply data
  mov    B, DDISP                    ; Copy data from result to display
  add    ASCII_OFFSET, DDISP         ; Add offset to display single digit
  inc    FDISP                       ; Set display flag
  halt

A:
  .data 0
B:
  .data 0
ASCII_OFFSET:
  .data 48
