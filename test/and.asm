; m[op2] = m[op2] - m[op1]
; if (m[op2] ≤ 0) pc = op3


TOP:
  subleq  0, A, SECOND_Z_CHECK    ; Checking if A's MSB is 1
  jmp     CONT_LOOP
CHECK_B:
  subleq  0, B, SECOND_Z_CHECK_B  ; If not, check B's MSB
  jmp     CONT_LOOP
CASE_ONE:
  add     0x18, TOTAL             ; Only add to TOTAL if A's MSB OR B's MSB is 1
CONT_LOOP:
  add     A, A                    ; Shift A one bit left
  add     B, B                    ; Shift B one bit left
  subleq  0x4, CASE_ONE           ; Dec pointer to powers of two
  subleq  0x4, LOOP_VAR, DONE     ; Dec loop var and branch if done
  jmp     TOP

DONE:
  mov     TOTAL, A
  halt

SECOND_Z_CHECK:
  subleq  A, 0, CHECK_B
  jmp     CHECK_B
SECOND_Z_CHECK_B:
  subleq  B, 0, CATCH_EDGE
  jmp     CASE_ONE
CATCH_EDGE:
  mov     EDGE_BAK, EDGE
  subleq  B, EDGE, CATCH_EDGE2
  jmp     CONT_LOOP
CATCH_EDGE2:
  mov     EDGE_BAK, EDGE
  add     B, SAVE_B
  subleq  EDGE, B, CASE_ONE
  mov     SAVE_B, B
  jmp     CONT_LOOP
;CATCH_EDGEA:
;  mov     EDGE_BAK, EDGE
;  subleq  A, EDGE, CATCH_EDGE2
;  jmp     CONT_LOOP
;CATCH_EDGE2A:
;  mov     EDGE_BAK, EDGE
;  add     A, SAVE_A
;  subleq  EDGE, A, CHECK_B
;  mov     SAVE_A, A
;  jmp     CONT_LOOP


LOOP_VAR:
  .data 16
A:
  .data 0b1010101010101010
B:
  .data 0b1010101010101010
TOTAL:
  .data 0
EDGE:
  .data 0x8000
EDGE_BAK:
  .data 0x8000
SAVE_B:
  .data 0
SAVE_A:
  .data 0
