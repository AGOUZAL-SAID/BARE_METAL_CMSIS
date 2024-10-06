.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start
_start:
ldr r0,= 0xdeadbeef
ldr r1,= 0x10000000
mov r2,#0
mov r3,#64
loop:
SUBS r5,r3,r2
beq  copy
str r0,[r1]
add r1,r1,#4
add r2,r2,#1
b loop

copy:
ldr r1,= 0x10000000
ldr r3,= 0x100
ldr r0,=0x10000300
loop2: 
ldr r9,[r1]
str r9,[r0]
add r1,r1,#4
add r0,r0,#4
SUBS r3,r3,#-4
bne loop2

end : 
b end 
