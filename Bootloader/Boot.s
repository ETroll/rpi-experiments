
.globl _start
_start:
    b RESET

.space 0x200000-0x8004,0

.globl RESET
RESET:
    @better location for a SP?
    mov sp, #0x08000000
    bl bootloader
hang:
    b hang

@   |  Stack |
@   :--------:
@   |  Boot  |
@   |  Code  |

.globl NOP
NOP:
    mov r0, r0

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl BRANCHTO
BRANCHTO:
    bx r0
