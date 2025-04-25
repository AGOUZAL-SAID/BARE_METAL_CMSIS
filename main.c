#include "clocks.h"      // Inclusion des fonctions d'initialisation et de gestion des horloges système
#include "irq.h"         // Inclusion des fonctions de configuration des interruptions (IRQ)
#include "matrix.h"      // Inclusion des fonctions liées à la gestion d'une matrice (ex: clavier matriciel)
#include <stdint.h>      // Inclusion des types entiers à taille fixe (uint8_t, uint32_t, etc.)
#include "uart.h"        // Inclusion des fonctions de communication UART
#include "buttons.h"     // Inclusion des fonctions de gestion des boutons
#include "led.h"         // Inclusion des fonctions de gestion des LED
#include "uart_irq.h"    // Inclusion des fonctions spécifiques à la gestion des interruptions UART
#include "timer.h"       // Inclusion des fonctions de configuration et gestion du timer

int main(){
    // Initialisation des horloges système (configuration de la fréquence et activation des périphériques)
    clocks_init();

    // Initialisation des LED (configuration des broches en sortie pour le contrôle des LED)
    led_init();

    // Initialisation de l'UART avec un débit de 38400 bauds
    uart_init(38400);

    // Initialisation de la matrice (par exemple, un clavier matriciel)
    matrix_init();

    // Initialisation des interruptions globales et configuration des vecteurs d'interruption
    irq_init();

    // Initialisation des boutons (configuration des entrées et des interruptions associées aux boutons)
    button_init();

    // Initialisation de la tram (probablement pour une gestion de mémoire ou d'une zone tampon spécifique)
    init_tram();

    // Activation des interruptions pour l'UART (permet de gérer les événements de communication via interruption)
    enable_interruption_uart();

    // Initialisation du timer avec une fréquence définie par (1000000/480)
    // Cette valeur détermine la période du timer (par exemple, en microsecondes)
    timer_init(1000000/480);
}
