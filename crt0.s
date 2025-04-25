.section .copage_section, "ax",%progbits
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start
.thumb_func
_start:
    ldr sp, =_stack
    bl copy_sections
    bl init_bss
    bl main
_exit:
    b _exit
.section .copage_section, "ax", %progbits  @ Définition de la section pour le code d'initialisation
                                      @ "ax" : section exécutable et allocable
                                      @ %progbits : contient des données en mémoire (contrairement à .bss qui est zéro-initialisée)

.syntax unified       @ Active la syntaxe unifiée d'ARM (compatible ARM/Thumb)
.arch armv7-m         @ Définit l'architecture comme ARMv7-M (Cortex-M4)
.cpu cortex-m4        @ Spécifie le processeur cible (Cortex-M4)
.thumb                @ Active le mode Thumb (obligatoire pour les Cortex-M)

.global _start        @ Rend _start accessible par d'autres fichiers (point d'entrée du programme)
.thumb_func           @ Indique que _start est une fonction Thumb

_start:
    ldr sp, =_stack   @ Initialise le pointeur de pile (SP) avec l'adresse définie dans le script linker
                       @ _stack = fin de sram2 (0x10008000) selon le script linker

    bl copy_sections  @ Copie les sections .data et .text depuis la Flash vers la RAM (si nécessaire)
                       @ Important car .data doit être en RAM pour stocker les variables modifiables

    bl init_bss       @ Initialise la section .bss (remplit avec des zéros toutes les variables non initialisées)
                       @ Obligatoire selon la norme C pour garantir des valeurs définies

    bl main           @ Appelle la fonction main() du programme principal
                       @ Normalement, main() ne devrait jamais se terminer

_exit:
    b _exit           @ Boucle infinie si main() se termine pour éviter un comportement indéfini
                       @ Une amélioration serait d'ajouter "wfi" pour réduire la consommation d'énergie
