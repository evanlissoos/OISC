; B / A UNSIGNED

QUOTIENT:
  .data   0x0000              ; Need mem location to store intermediate result
TEMP_Z:
  .data   0x0000              ; Since we know it starts at zero, we can do this
  .data   FIRST_Z_CHECK       ; Effectively NOP, but now can use memory for calculation

  ; Divide by zero checks
FIRST_Z_CHECK:
  subleq  0, A, SECOND_Z_CHECK; Can't divide by zero

  ; Main division loop
TOP:
  subleq  A, B, DONE          ; if (B - A) > 0 continue
  inc     QUOTIENT
  jmp     TOP

DONE:
  ; B = remainder
  subleq  B, TEMP_Z, REM_ZERO ; Check if remainder zero
  add     A, B                ; If not, need to add A to B to get remainder

MOV_A:
  ; A = quotient
  mov     QUOTIENT, A

END:
  halt

SECOND_Z_CHECK:
  subleq  A, 0, END           ; Can't divide by zero
  subleq  0, 0, TOP           ; Reset zero and jump back

REM_ZERO:
  inc     QUOTIENT            ; If so, need to increment quotient
  jmp     MOV_A


A:
  .data 6
B:
  .data 10
