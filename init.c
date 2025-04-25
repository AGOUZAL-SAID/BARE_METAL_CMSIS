#include <stdint.h>  // Inclusion du header pour les types standard à largeur fixe

// Déclaration des symboles définis par le linker pour le début et la fin de la section BSS
extern uint8_t _bstart;  // Adresse de début de la section BSS
extern uint8_t _bend;    // Adresse de fin de la section BSS

// Fonction pour initialiser la section BSS à zéro
void init_bss(){
    // Pointeur initialisé à l'adresse de début de la section BSS
    uint8_t *p = (uint8_t *)&_bstart;
    
    // Pointeur marquant la fin de la section BSS
    uint8_t *finish = (uint8_t *)&_bend;
    
    // Boucle d'initialisation : on parcourt toute la section BSS
    while (p <= finish){
        *p = 0;  // Mise à zéro de la case mémoire pointée par p
        p++;     // Passage à l'octet suivant
    }  
}
