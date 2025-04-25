#include "memfuncs.h" // Inclusion des fonctions de gestion mémoire (ex: memcpy)

/* Déclaration des symboles provenant du linker, qui représentent
   les adresses de départ (LMA) et d'arrivée (VMA) pour les différentes sections,
   ainsi que leur taille. Ces symboles sont généralement définis dans le script de linker. */
extern uint8_t  LMA_vector;  // Adresse de départ (Load Memory Address) de la section vectorielle
extern uint8_t  LMA_text;    // Adresse de départ de la section texte (code exécutable)
extern uint8_t  LMA_rodata;  // Adresse de départ de la section des données en lecture seule
extern uint8_t  LMA_data;    // Adresse de départ de la section data (données initialisées)
extern uint8_t  LMA_bss;     // Adresse de départ de la section bss (données non initialisées)

extern uint8_t VMA_vector;   // Adresse de destination (Virtual Memory Address) pour la section vectorielle
extern uint8_t VMA_text;     // Adresse de destination pour la section texte
extern uint8_t VMA_rodata;   // Adresse de destination pour la section rodata
extern uint8_t VMA_data;     // Adresse de destination pour la section data
extern uint8_t _bstart;      // Adresse de destination pour la section bss

extern uint32_t LENGTH_vector;  // Taille de la section vectorielle
extern uint32_t LENGTH_text;    // Taille de la section texte
extern uint32_t LENGTH_rodata;  // Taille de la section rodata
extern uint32_t LENGTH_data;    // Taille de la section data
extern uint32_t LENGTH_bss;     // Taille de la section bss

// Attribut pour placer la fonction dans la section ".copage_section"
__attribute__((section(".copage_section")))
void copy_sections(){
    // Copie de la section texte (code exécutable) de LMA vers VMA
    memcpy(&VMA_text, &LMA_text, (uint32_t)&LENGTH_text);

    // Copie de la section bss (données non initialisées) de LMA vers VMA,
    // ici l'adresse de destination est indiquée par _bstart
    memcpy(&_bstart, &LMA_bss, (uint32_t)&LENGTH_bss);

    // Copie de la section data (données initialisées) de LMA vers VMA
    memcpy(&VMA_data, &LMA_data, (uint32_t)&LENGTH_data);

    // Copie de la section vectorielle (table des vecteurs d'interruptions) de LMA vers VMA
    memcpy(&VMA_vector, &LMA_vector, (uint32_t)&LENGTH_vector);
}
