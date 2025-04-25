#include <stdint.h>

// Définition du type size_t (typiquement défini dans <stddef.h> ou <stdlib.h>)
typedef unsigned int size_t ;

/*
 * Fonction memset : remplit une zone mémoire avec une valeur donnée.
 *
 * Paramètres :
 *   bstart : pointeur vers le début de la zone mémoire à remplir
 *   a      : la valeur à copier (sera convertie en uint8_t)
 *   size   : le nombre d'octets à remplir
 *
 * Renvoie :
 *   le pointeur de départ (bstart)
 *
 * Remarque : La boucle utilise la variable 'finish' pour compter jusqu'à size.
 * Cependant, 'finish' n'est jamais incrémentée, ce qui provoque une boucle infinie.
 */
void * memset(void * bstart, int a, size_t size){
    unsigned int finish = 0;
    uint8_t * p = (uint8_t *) bstart;
    while (finish <= size){
        *p = (uint8_t) a;
        p++;
        // Incrémentation manquante de finish pour avancer dans la boucle
        finish++;
    }
    return bstart;
}

/*
 * Fonction memcmp : compare deux zones mémoire octet par octet.
 *
 * Paramètres :
 *   mem1_p : pointeur vers la première zone mémoire
 *   mem2_p : pointeur vers la deuxième zone mémoire
 *   size   : nombre d'octets à comparer
 *
 * Renvoie :
 *   0 si les zones sont identiques,
 *   une valeur négative ou positive selon la différence du premier octet différent.
 *
 * Remarque : Les pointeurs sont incrémentés dans l'expression, ce qui fonctionne,
 * mais il est souvent préférable d'utiliser des pointeurs temporaires pour la clarté.
 */
int memcmp( const void * mem1_p, const void * mem2_p, size_t size ){ 
    for(unsigned int position = 0; position < size; ++position ) {
        int cmp = *( (uint8_t *) mem1_p ) - *( (uint8_t *) mem2_p );
        if (cmp) return cmp;
        // Incrément des pointeurs pour comparer l'octet suivant
        mem1_p = (uint8_t *)mem1_p + 1;
        mem2_p = (uint8_t *)mem2_p + 1;
    }
    return 0;
} 

/*
 * Fonction memcpy : copie une zone mémoire source vers une zone mémoire destination.
 *
 * Paramètres :
 *   destination : pointeur vers la zone de destination
 *   source      : pointeur vers la zone source
 *   size        : nombre d'octets à copier
 *
 * Renvoie :
 *   Le pointeur vers la zone destination (mais ici, le pointeur retourné est déplacé à la fin)
 *
 * Remarque : 
 *   - La fonction est placée dans une section spéciale grâce à __attribute__((section(".copage_section"))).
 *   - Attention, le pointeur destination est modifié au cours de la copie ; 
 *     si l'on souhaite renvoyer le pointeur de départ, il faudrait le sauvegarder.
 */
__attribute__((section(".copage_section"))) 
void * memcpy( void * destination, const void * source, size_t size ){ 
    for (unsigned int position = 0; position < size; ++position ){
        *( (uint8_t *)destination ) = *( (uint8_t *)source );
        destination = (uint8_t *)destination + 1;
        source = (uint8_t *)source + 1; 
    }  
    return destination; // Retourne le pointeur à la fin de la zone destination copiée
}  

/*
 * Fonction memmove : copie une zone mémoire qui peut se chevaucher.
 *
 * Paramètres :
 *   destination : pointeur vers la zone de destination
 *   source      : pointeur vers la zone source
 *   size        : nombre d'octets à copier
 *
 * Renvoie :
 *   Le pointeur vers la zone destination (ici modifié pour pointer à la fin)
 *
 * Remarque :
 *   - Cette implémentation est très basique et ne gère pas correctement le chevauchement.
 *   - Le test "if (destination != source)" n'a pas de sens dans ce contexte, car si
 *     destination et source sont égaux, la copie est triviale, mais cela ne permet pas
 *     de gérer le cas où destination > source (ou inversement) en cas de chevauchement.
 */
void * memmove( void * destination, const void * source, size_t size ){ 
    uint8_t intermedium = 0;
    for (unsigned int position = 0; position < size; ++position ){
        if (destination != source){
            *( (uint8_t *)destination ) = *( (uint8_t *)source );
            destination = (uint8_t *)destination + 1;
            source = (uint8_t *)source + 1;
        } else{
            // Si les pointeurs sont identiques, copie triviale (mais ce cas ne se produit normalement pas)
            intermedium = *( (uint8_t *)source ); 
            *( (uint8_t *)destination ) = intermedium;
            source = (uint8_t *)source + 1;
            destination = (uint8_t *)destination + 1;
        }     
    }  
    return destination;
}
