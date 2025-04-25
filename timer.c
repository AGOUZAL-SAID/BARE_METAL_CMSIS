#include "stm32l475xx.h"         // Définitions spécifiques au microcontrôleur STM32L475xx
#include "system_stm32l4xx.h"     // Fonctions de configuration système (horloges, etc.)
#include "core_cm4.h"           // Définitions pour le cœur Cortex-M4
#include "led.h"                // Fonctions de gestion des LED
#include "matrix.h"             // Fonctions de gestion de la matrice LED
#include "time.h"               // Fonctions et définitions liées au temps

extern uint8_t trame_global[192]; // Tableau global contenant les données (trame) à afficher

/*
 * Fonction d'initialisation du timer TIM2
 * Paramètre : max_us -> valeur d'auto-recharge (ARR) en microsecondes
 */
void timer_init(int max_us)
{
    // Activation de l'horloge pour TIM2 via le registre APB1ENR1 :
    // Désactive d'abord TIM2 en masquant la valeur actuelle puis en configurant le bit TIM2EN
    RCC->APB1ENR1 = (RCC->APB1ENR1 & ~(RCC_APB1ENR1_TIM2EN_Msk)) | (1 << RCC_APB1ENR1_TIM2EN_Pos);
    
    // Réinitialise le flag d'interruption de mise à jour (UIF) dans le registre de statut de TIM2
    TIM2->SR = (TIM2->SR & ~(TIM_SR_UIF_Msk));
    
    // Réinitialise le compteur de TIM2
    TIM2->CNT = (TIM2->CNT & ~(TIM_CNT_CNT_Msk));
    
    // Configure le registre de contrôle CR1 :
    // Efface les bits CMS (Center-aligned mode) et DIR (direction du compteur)
    TIM2->CR1 = (TIM2->CR1 & ~(TIM_CR1_CMS_Msk) & ~(TIM_CR1_DIR_Msk));
    
    // Configure le prescaler (PSC) pour obtenir une période d'horloge adaptée :
    // Ici, on charge la valeur 79 pour diviser l'horloge par 80 (puisque le compteur commence à 0)
    TIM2->PSC = (TIM2->PSC & ~(TIM_PSC_PSC_Msk)) | (79 << TIM_PSC_PSC_Pos);
    
    // Configure le registre d'auto-recharge (ARR) pour définir la durée du timer en microsecondes
    TIM2->ARR = (TIM2->ARR & ~(TIM_ARR_ARR_Msk)) | (max_us << TIM_ARR_ARR_Pos);
    
    // Active l'interruption de mise à jour (UIE) pour TIM2
    TIM2->DIER = (TIM2->DIER & ~(TIM_DIER_UIE_Msk)) | (1 << TIM_DIER_UIE_Pos);
    
    // Active l'interruption dans le NVIC pour TIM2
    // Le paramètre "28" correspond à l'IRQ de TIM2 (vérifier la référence pour être sûr)
    NVIC_EnableIRQ(28);
    
    // Démarre le timer TIM2 en activant le bit CEN dans CR1
    TIM2->CR1 = (TIM2->CR1 & ~(TIM_CR1_CEN_Msk)) | (1 << TIM_CR1_CEN_Pos);
}

// Variables statiques utilisées par l'interruption du timer
static int ligne = 0;  
// Pointeur sur la fin de la trame globale (dernier octet de la trame)
static uint8_t *trame_timer_end = &trame_global[191];

/*
 * Gestionnaire d'interruption pour TIM2.
 * À chaque mise à jour du timer, cette ISR :
 *   - Réinitialise le flag d'interruption,
 *   - Désactive toutes les lignes de la matrice,
 *   - Envoie une série de données depuis trame_global,
 *   - Active la ligne correspondante pour afficher la donnée,
 *   - Passe à la ligne suivante.
 */
void TIM2_IRQHandler(void){
    // Efface le flag d'interruption de mise à jour pour éviter de retomber immédiatement dans l'ISR
    TIM2->SR = (TIM2->SR & ~(TIM_SR_UIF_Msk));    
    
    // Désactive toutes les lignes de la matrice pour préparer l'affichage de la nouvelle ligne
    deactivate_rows();
    
    // Si toutes les lignes ont été parcourues (8 lignes), réinitialise le pointeur
    // et remet la variable ligne à 0 pour recommencer l'affichage
    if (ligne == 8)
    {
        trame_timer_end = &trame_global[191];
        ligne = 0;
    }
    
    // Pour chaque ligne, on envoie 24 octets (24 * 8 = 192 octets au total pour 8 lignes)
    // Chaque pixel semble être représenté par 3 octets (R, G, B)
    for (int j = 0; j < 24; j++)
    {
        // Envoie l'octet pointé par trame_timer_end puis décrémente le pointeur
        send_byte(*trame_timer_end--);
    }
    
    // Génère une impulsion sur LAT (latch) pour valider l'envoi des données
    pulse_LAT();
    
    // Active la ligne correspondante en inversant l'ordre des lignes pour l'affichage (7 - ligne)
    activate_row(7 - ligne);
    
    // Passe à la ligne suivante pour la prochaine interruption
    ligne++;
}
