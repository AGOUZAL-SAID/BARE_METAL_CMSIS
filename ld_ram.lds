MEMORY
{
    rom (rx)   : ORIGIN = 0x08000000, LENGTH = 1M   /* Flash ROM (exécutable, lecture seule) */
    sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K  /* Première RAM, lecture/écriture */
    sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K  /* Deuxième RAM, lecture/écriture */
}

_stack = ORIGIN(sram2) + LENGTH(sram2);  /* Initialisation du pointeur de pile à la fin de sram2 */

/* Déclaration des adresses de chargement en mémoire flash (LMA) */
LMA_vector  = LOADADDR(.vector_table);
LMA_text    = LOADADDR(.text);
LMA_data    = LOADADDR(.data);
LMA_bss     = LOADADDR(.bss);

/* Calcul de la taille de chaque section */
LENGTH_vector  = SIZEOF(.vector_table);
LENGTH_text    = SIZEOF(.text);
LENGTH_data    = SIZEOF(.data);
LENGTH_bss     = SIZEOF(.bss);

SECTIONS {

    /* Table des vecteurs d'interruptions (doit être placée en RAM pour certains systèmes) */
    .vector_table : {
        VMA_vector = .;  /* Adresse virtuelle (VMA) */
        *(.vector_table) /* Inclusion des symboles */
    } >sram1 AT>rom /* Chargé en ROM mais exécuté en RAM */
    
    /* Section spécifique pour la mémoire cache/page (rarement utilisée, vérifier son utilité) */
    .copage_section : {
        *(.copage_section)
    }>rom /* Stocké en ROM */

    /* Code exécutable */
    .text : {
        VMA_text = . ;
        *(.text)  /* Inclusion du code */
    }>sram1 AT>rom /* Chargé en ROM et exécuté en RAM */

    /* Données constantes en mémoire Flash */
    .rodata : {
        *(.rodata)
    }>rom /* Stocké uniquement en ROM */

    /* Données initialisées en RAM */
    .data : {
        VMA_data = . ;
        *(.data)
    }>sram1 AT>rom /* Chargé en ROM et copié en RAM au démarrage */

    /* Variables non initialisées (BSS) */
    .bss : {
        _bstart = .; /* Début de la section */
        *(.bss)   /* Inclusion des variables non initialisées */
        _bend = .; /* Fin de la section */
    }>sram1 AT>rom /* Alloué en RAM mais non stocké en ROM */
}

ENTRY(_start) /* Définition du point d'entrée du programme */
