; B / A UNSIGNED

QUOTIENT:
  .data   0x0000              ; Need mem location to store intermediate result
TEMP_Z:
  .data   0x0000              ; Since we know it starts at zero, we can do this
  .data   FIRST_Z_CHECK       ; Effectively NOP, but now can use memory for calculation

  ; Divide by zero checks
FIRST_Z_CHECK:
  subleq  0, A, END; Can't divide by zero
  jmp     SECOND_Z_CHECK

  ; Main division loop
TOP:
  subleq  A, B, DONE          ; if (B - A) > 0 continue
  inc     QUOTIENT
  jmp     TOP

DONE:
  ; B = remainder
  subleq  TEMP_Z, 

  subleq  B, TEMP_Z
  ; Manual mov so we can jump if remainder zero
  subleq  B, B
  subleq  TEMP_Z, 0
  subleq  0, B, REM_ZERO
END_MOV_B:
  subleq  0, 0

  ; A = quotient
  mov     QUOTIENT, A



END:
  subleq  0, 0                ; Reset zero
  halt

SECOND_Z_CHECK:
  subleq  A, 0, END           ; Can't divide by zero
  subleq  0, 0                ; Reset zero
  jmp TOP

REM_ZERO:
  inc     QUOTIENT
  jmp     END_MOV_B


A:
  .data 6
B:
  .data 10
