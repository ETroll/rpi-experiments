.globl _start
_start:
    bl k_main
hang: b hang


.globl NOP
NOP:
    nop

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr
