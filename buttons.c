#include "stm32l475xx.h"    // Inclusion des définitions spécifiques au microcontrôleur STM32L475xx
#include "buttons.h"       // Inclusion du header pour la gestion des boutons
#include "led.h"           // Inclusion du header pour la gestion des LED

// Fonction d'initialisation du bouton
void button_init() {
    // Activation de l'horloge pour le port GPIOC (pour le bouton sur la broche PC13)
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN;

    // Configuration de la broche PC13 en mode entrée
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE13_Msk);

    // Configuration de la broche PC13 comme source d'interruption externe
    // On sélectionne le port GPIOC pour l'EXTI13 dans le registre SYSCFG->EXTICR[3]
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~(SYSCFG_EXTICR4_EXTI13)) | (2 << SYSCFG_EXTICR4_EXTI13_Pos);

    // Activation de l'interruption sur la broche 13
    EXTI->IMR1 = (EXTI->IMR1 & ~(EXTI_IMR1_IM13_Msk)) | (1 << EXTI_IMR1_IM13_Pos);

    // Désactivation du déclenchement sur front montant pour EXTI13
    EXTI->RTSR1 = (EXTI->RTSR1 & ~(EXTI_RTSR1_RT13_Msk));

    // Activation du déclenchement sur front descendant pour EXTI13
    EXTI->FTSR1 = (EXTI->FTSR1 & ~(EXTI_FTSR1_FT13_Msk)) | (1 << EXTI_FTSR1_FT13_Pos);

    // Activation de l'interruption dans le NVIC avec la priorité par défaut
    NVIC_EnableIRQ(40);   // Le paramètre "40" correspond à l'IRQ pour EXTI15_10
}

// Gestionnaire d'interruption pour les broches EXTI15_10 (donc y compris PC13)
void EXTI15_10_IRQHandler(void) { 
    // Variable statique pour mémoriser l'état actuel (0 = LED éteinte, 1 = LED allumée)
    static uint8_t etat = 0;

    // Si la LED est éteinte, on l'allume
    if(etat == 0) {
        led_g_on();
        etat = 1;
    }
    // Sinon, si la LED est allumée, on l'éteint
    else {
        led_g_off();
        etat = 0;
    }

    // Effacement du flag d'interruption pour EXTI13 afin de pouvoir détecter la prochaine interruption
    EXTI->PR1 = (EXTI->PR1 & ~(EXTI_PR1_PIF13_Msk)) | (1 << EXTI_PR1_PIF13_Pos);
}
