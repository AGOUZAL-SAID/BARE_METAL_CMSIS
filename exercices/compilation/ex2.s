.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

_start:
    ldr     r0, =mota  @ Charger l'adresse de pointeur ver a 
    ldr     r1, =motb  @ Charger l'adresse de pointeur ver b
    ldr     r2, =motc  @ Charger l'adresse de pointeur ver c
    ldr     r3, [r2]     @ Charger la valeur du pointeur c 
    ldr     r6, [r3]     @ Charger la valeur pointée par c dans r6 ( valeur *c)
    ldr     r4, [r0]     @ Charger la valeur du pointeur a dans r4
    ldr     r7, [r4]     @ Charger la valeur pointée par a (valeur de *a)
    add     r5, r6, r7   @ Ajouter *c à *a
    str     r5, [r4]     @ Stocker le résultat dans *a

    ldr     r4, [r1]     @ Charger l'adresse du pointeur b dans r4
    ldr     r7, [r4]     @ Charger la valeur pointée par b (valeur de *b)
    add     r5, r6, r7   @ Ajouter *c à *b
    str     r5, [r4]     @ Stocker le résultat dans *b

end:
    b       end          @ Boucle infinie

mota:
    .word   12025658      @ Déclaration de l'adresse de a
motb:
    .word   168892        @ Déclaration de l'adresse de b
motc:
    .word   15795263      @ Déclaration de l'adresse de c