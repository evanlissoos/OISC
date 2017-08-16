; A >> B

CALC_OFF:
  subleq  B, TEMPZ1               ; Calculating and storing base2 offset
  subleq  TEMPZ1, TOP
  subleq  B, B                    ; Clear out B


; Main division loop
TOP:
  subleq  POW2, A, DONE          ; if (A - EXP2) > 0 continue
  inc     B                      ; B will hold the result
  jmp     TOP

DONE:
  subleq  A, TEMPZ2, REM_ZERO
END:
  halt

REM_ZERO:
  inc B
  jmp END

A:
  .data 0x00FF
B:
  .data 8
TEMPZ1:
  .data 0
TEMPZ2:
  .data 0
