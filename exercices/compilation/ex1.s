.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start


_start:
    ldr r0, =mota
    ldr r2,=#0 
    str r2,[r0]


init:
    ldr     r3,[r0] 
    ldr     r1,=#0
function_f:
    CMP     r1,#255
    bgt     init
    CMP     r2, r1 
    bgt     function_g

end:
    B       end 

function_g:
    add     r5,r5,r5
    add     r1,r1,#1 
    b       function_f
mota:    
    .word 15


