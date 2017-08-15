; A << B
subleq  0, B, DONE          ; Check for zero for negative condition
TOP:
  add     A, A              ; Shift left one bit and store back in A
  subleq  POS_ONE, B, DONE  ; Decrement B and if it's zero, done
  jmp     TOP               ; Jump back to the top if not

DONE:
  halt

A:
  .data  0x1
B:
  .data  3
