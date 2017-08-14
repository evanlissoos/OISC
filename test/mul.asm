TOTAL:
  .data   0x0000             ; Need mem location to store intermediate result
  .data   0x0000             ; Since we know it starts at zero, we can do this
  .data   START              ; Effectively NOP, but now can use memory for calculation
START:
  inc     0xB                ; Add one to B
TOP:
  subleq  POS_ONE, 0xB, DONE ; If (B - 1) is 0, done
  add     0xA,  TOTAL        ; Add A to total
  jmp     TOP                ; Go to top of loop

DONE:
  ; We add here because we know B must be zero and add is more efficient than mov
  add     TOTAL, 0xB         ; Store total in B
  jmp     0
