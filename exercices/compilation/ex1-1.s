.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

_start:
    ldr     r0, =mota     @ Charger l'adresse de w_a dans r0
    ldr     r2, =#0       @ Initialiser r2 (a) à 0
    str     r2, [r0]      @ Stocker 0 à l'adresse de w_a
    ldr     r3, [r0]      @ Charger la valeur de w_a dans r3
    ldr     r1, =#0       @ Initialiser r1 (i) à 0

function_f:
    CMP     r2, r1        @ Comparer r2 et r1
    bgt     function_g    @ Si r2 > r1, aller à function_g

end:
    B       end           @ Boucle infinie

function_g:
    add     r5, r5, r5    @ Effectuer une opération sur r5 (non précisé dans le C)
    add     r1, r1, #1    @ Incrémenter r1
    b       function_f    @ Retourner à function_f

mota:
    .word 15              @ Déclaration de la variable w_a, contenant a


