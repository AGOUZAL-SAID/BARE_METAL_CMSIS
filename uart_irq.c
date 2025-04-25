#include "uart.h"               // Fonctions et définitions pour la communication UART
#include "uart_irq.h"           // Fonctions spécifiques à la gestion des interruptions UART
#include "stm32l475xx.h"        // Définitions spécifiques au microcontrôleur STM32L475xx
#include "system_stm32l4xx.h"    // Configuration système (horloges, etc.)
#include "core_cm4.h"          // Définitions pour le cœur Cortex-M4

extern uint8_t trame_global[192];  // Déclaration d'un tableau global contenant la trame à recevoir ou afficher

// Pointeur qui pointe sur le début de la trame dans trame_global.
// Il est utilisé pour stocker les données reçues via UART.
uint8_t * trame_depart = &trame_global[0];

// Variable statique qui garde la position actuelle dans la trame.
// Elle est incrémentée à chaque octet reçu.
static uint8_t position_in_trame = 0;

/*
 * Gestionnaire d'interruption pour USART1.
 * Cette fonction est appelée lorsqu'une interruption est générée par USART1 (par exemple,
 * lorsque de nouvelles données sont reçues).
 */
void USART1_IRQHandler(void) {
    // Récupère le caractère reçu depuis l'UART via la fonction uart_getchar().
    uint8_t data = uart_getchar();

    /*
     * Vérification des erreurs de trame :
     * On vérifie si le flag d'erreur de trame (FE) ou d'overrun (ORE) n'est pas levé.
     * L'opérateur '~' est utilisé pour inverser le masque, puis on utilise l'opérateur &
     * pour s'assurer que ces erreurs ne sont pas présentes.
     */
    if(~(USART1->ISR & USART_ISR_FE_Msk) & ~(USART1->ISR & USART_ISR_ORE_Msk)) {
        /*
         * Si le caractère reçu est 0xff ou que la trame est complète (192 octets),
         * on réinitialise le pointeur et la position.
         */
        if((data == 0xff) | (position_in_trame == 192)){
            trame_depart = &trame_global[0];
            position_in_trame = 0;
        }
        else {
            // Sinon, on stocke le caractère dans la trame et on incrémente le pointeur et la position
            *trame_depart = data;
            trame_depart++;
            position_in_trame++;
        }
    }
    else {
        /*
         * En cas d'erreur (erreur de framing ou overrun) :
         * Si le caractère reçu est 0xff, cela semble marquer la fin ou le début d'une nouvelle trame.
         * On réinitialise alors le pointeur et la position.
         */
        if(data == 0xff ){
            trame_depart = &trame_global[0];
            position_in_trame = 0;
            // Efface le flag d'erreur de framing (FECF) en écrivant dans le registre ICR
            USART1->ICR = (USART1->ICR & ~(USART_ICR_FECF_Msk)) | (1 << USART_ICR_FECF_Pos);
            // Efface le flag d'erreur overrun (ORECF) de la même manière
            USART1->ICR = (USART1->ICR & ~(USART_ICR_ORECF_Msk)) | (1 << USART_ICR_ORECF_Pos);
        }
    }
}

/*
 * Fonction d'activation des interruptions UART.
 * Elle active l'interruption RXNE (réception de données) dans le registre de contrôle CR1
 * de USART1 et active l'IRQ correspondante dans le NVIC.
 */
void enable_interruption_uart(){
    // Active le bit RXNEIE pour générer une interruption à la réception d'un octet
    USART1->CR1 = (USART1->CR1 & ~(USART_CR1_RXNEIE_Msk)) | (1 << USART_CR1_RXNEIE_Pos);
    // Active l'interruption USART1 dans le NVIC
    NVIC_EnableIRQ(37);
}
