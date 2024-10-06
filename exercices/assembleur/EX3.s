.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start
_start:
/*premier remplisssage et copage par 0xdeadbeef*/
ldr r0,=0x10000000
ldr r1,= 0xdeadbeef
ldr r2,= 256
bl etape1

ldr r0, =0x10000300
ldr r1, =0x10000000
ldr r2, =256
bl etape2 

/* deuxiemme remplissage et copage 0xcafecafe*/

ldr r0,=0x10003000
ldr r1,= 0xcafecafe
ldr r2,= 64
bl etape1

ldr r0, =0x10006000
ldr r1, =0x10003000
ldr r2, =32
bl etape2 


/*remplissage*/

etape1:
subs r2,r2,#-4
beq  endEtape1
str r1,[r0]
add r0,r0,#4
b etape1
endEtape1:
bx lr

/*copage*/

etape2: 
ldr r9,[r1]
str r9,[r0]
add r1,r1,#4
add r0,r0,#4
SUBS r2,r2,#-4
bne etape2
bx lr

