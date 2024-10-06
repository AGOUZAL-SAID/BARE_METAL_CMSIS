.syntax unified
.arch armv7-m
.cpu cortex-m4
leMot:
.asciz "Bonjour le monde!" 
.thumb

.global _start
_start:

/*premier remplisssage "Bonjour le monde!"/

ldr r0,=0x10000000
ldr r1,= leMot
bl etape1

/* deuxiemme remplissage "Bonjour le monde!"*/

ldr r0,=0x10003000
ldr r1,= leMot
bl etape1

END:
B END


/*remplissage*/

etape1:
ldrb    r2, [r1], #1           // Charger un octet depuis l'adresse source (r0), puis incrémenter r0
strb    r2, [r0], #1           // Stocker l'octet à l'adresse destination (r1), puis incrémenter r1
cmp     r2, #0                 // Comparer l'octet à 0 (fin de chaîne)
bne     etape1                 // Si l'octet n'est pas nul, continuer la boucle
bx      lr                     // Retourner à l'appelant

