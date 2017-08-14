subleq a, 0 ; This is a test comment
subleq 0, b
subleq 0, 0
loop:
jmp     loop
a:
.data 1
b:
.data 2
