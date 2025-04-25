#include "led.h"          // Inclusion de l'interface pour la gestion des LEDs
#include "stm32l475xx.h"  // Inclusion des définitions spécifiques au microcontrôleur STM32L475xx

// Définition d'adresses spécifiques en mode "bare metal"
// Ces définitions permettent d'accéder directement aux registres d'un port GPIO
#define REG_GPIOB_MODER    (*(volatile int *) 0x48000400)  // Registre de configuration de mode du port GPIOB
#define B_REG_BSRR         (*(volatile int *) 0x48000418)  // Registre de mise à jour du port GPIOB (set/reset)
#define REG_GPIOC_MODER    (*(volatile int *) 0x48000800)  // Registre de configuration de mode du port GPIOC
#define REG_BSRR_C         (*(volatile int *) 0x48000818)  // Registre de mise à jour du port GPIOC (set/reset)
#define REG_RCC_AHB2ENR    (*(volatile int *) 0x4002104c)  // Registre de contrôle d'horloge pour les ports GPIO

// Fonction d'initialisation des LED
void led_init(void) {
    // Activation des horloges pour les ports GPIOC et GPIOB via le registre RCC_AHB2ENR
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;
    
    // Configuration de la broche PB14 en mode "sortie"
    // Efface les bits de mode pour PB14 puis configure le mode "01" (sortie)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | (GPIO_MODER_MODE14_0);
}

// Fonction pour allumer la LED verte (LED sur PB14)
void led_g_on() {
    // Ecriture dans le registre BSRR pour mettre à l'état haut la broche PB14
    GPIOB->BSRR = GPIO_BSRR_BS14;
}

// Fonction pour éteindre la LED verte (LED sur PB14)
void led_g_off() {
    // Ecriture dans le registre BSRR pour mettre à l'état bas la broche PB14
    GPIOB->BSRR = GPIO_BSRR_BR14;
}

// Fonction générique de contrôle d'une LED avec un choix d'état (LED_YELLOW, LED_BLUE ou LED_OFF)
// La variable 'comand' est de type 'enum state' défini dans "led.h"
void led(enum state comand) {
    // Si la commande est d'allumer la LED jaune
    if (comand == LED_YELLOW) {
        // Configuration de la broche PC9 en mode sortie :
        // Efface les bits de mode pour PC9 puis configure en mode "01" (sortie)
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | (GPIO_MODER_MODE9_0);
        // Allume la LED jaune en mettant la broche PC9 à l'état haut
        GPIOC->BSRR = GPIO_BSRR_BS9;
    }
    
    // Si la commande est d'allumer la LED bleue
    if (comand == LED_BLUE) {
        // Configuration de la broche PC9 en mode sortie
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | (GPIO_MODER_MODE9_0);
        // Éteint la LED bleue en mettant la broche PC9 à l'état bas à l'aide du registre BSRR dédié
        REG_BSRR_C = GPIO_BSRR_BR9;
    }
    
    // Si la commande est d'éteindre la LED (aucune LED sur PC9)
    if (comand == LED_OFF) {
        // Réinitialise la configuration de la broche PC9 en effaçant les bits de mode
        REG_GPIOC_MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk);
    }
}
