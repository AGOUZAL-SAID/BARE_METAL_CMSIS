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
beq  end
str r0,[r1]
add r1,r1,#4
add r2,r2,#1
b loop
end:
b end 
