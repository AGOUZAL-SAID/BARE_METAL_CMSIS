#include "stm32l475xx.h"   // Définitions spécifiques au microcontrôleur STM32L475xx
#include "matrix.h"       // Interface pour la gestion de la matrice LED

// Symboles externes pour accéder à l'image binaire intégrée (définis par le linker)
extern uint8_t _binary_image_raw_start;
extern uint8_t _binary_image_raw_end;
extern uint8_t _binary_image_raw_size;

// Tableau global qui contient la "trame" (données) à afficher (192 octets)
uint8_t trame_global[192];

// Définition d'une structure pour représenter une couleur RVB (rouge, vert, bleu)
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

// Déclaration de trois tableaux de couleurs pour générer des dégradés
rgb_color dbleu[8];
rgb_color drouge[8];
rgb_color dvert[8];

/*
 * Initialisation d'un dégradé de bleu.
 * La valeur de 'b' (bleu) est modifiée pour chaque couleur,
 * tandis que les composantes rouge et verte sont à 0.
 */
void degrade_bleu_init(){
    uint8_t b = 5;
    rgb_color *pt = &dbleu[0]; 
    for(int i = 0; i < 8; i++){
        pt->r = 0;
        pt->g = 0;
        pt->b = b;
        pt++;
        b = 30 * (i + 2);  // Augmente la valeur bleue pour le dégradé
    } 
} 

/*
 * Initialisation d'un dégradé de rouge.
 * La composante rouge est modifiée, les autres sont à 0.
 */
void degrade_rouge_init(){
    uint8_t b = 5;
    rgb_color *pt = &drouge[0]; 
    for(int i = 0; i < 8; i++){
        pt->r = b;
        pt->g = 0;
        pt->b = 0;
        pt++;
        b = 30 * (i + 2);
    } 
} 

/*
 * Initialisation d'un dégradé de vert.
 * La composante verte est modifiée, les autres sont à 0.
 */
void degrade_vert_init(){
    uint8_t b = 5;
    rgb_color *pt = &dvert[0]; 
    for(int i = 0; i < 8; i++){    
        pt->r = 0;
        pt->g = b;
        pt->b = 0;
        pt++;
        b = 30 * (i + 2);
    } 
} 

/*
 * Contrôle de la broche RST (Reset) via GPIOC, bit 3.
 * Si x est non nul, on met la broche à l'état haut (activation), sinon bas (désactivation).
 */
void RST(int x){
    if(x){ 
        GPIOC->BSRR = GPIO_BSRR_BS3;
    } else { 
        GPIOC->BSRR = GPIO_BSRR_BR3;
    }
} 

/*
 * Contrôle de la broche SB (probablement "Select Bank" ou similaire) via GPIOC, bit 5.
 */
void SB(int x){
    if(x){ 
        GPIOC->BSRR = GPIO_BSRR_BS5;
    } else { 
        GPIOC->BSRR = GPIO_BSRR_BR5;
    }
}

/*
 * Contrôle de la broche LAT (Latch) via GPIOC, bit 4.
 */
void Lat(int x){
    if(x){ 
        GPIOC->BSRR = GPIO_BSRR_BS4;
    } else { 
        GPIOC->BSRR = GPIO_BSRR_BR4;
    }
}

/*
 * Contrôle de la broche SCK (Serial Clock) via GPIOB, bit 1.
 */
void SCK(int x){
    if(x){ 
        GPIOB->BSRR = GPIO_BSRR_BS1;
    } else { 
        GPIOB->BSRR = GPIO_BSRR_BR1;
    }
}

/*
 * Contrôle de la broche SDA (Serial Data) via GPIOA, bit 4.
 */
void SDA(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS4;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR4;
    }
}

/*
 * Fonctions pour contrôler les lignes de la matrice (ROW0 à ROW7).
 * Chaque fonction active (1) ou désactive (0) une ligne en manipulant
 * la broche correspondante (par exemple ROW0 sur GPIOB, bit 2, etc.).
 */
void ROW0(int x){
    if(x){ 
        GPIOB->BSRR = GPIO_BSRR_BS2;
    } else { 
        GPIOB->BSRR = GPIO_BSRR_BR2;
    }
}

void ROW1(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS15;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR15;
    }
}

void ROW2(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS2;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR2;
    }
}

void ROW3(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS7;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR7;
    }
}

void ROW4(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS6;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR6;
    }
}

void ROW5(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS5;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR5;
    }
}

void ROW6(int x){
    if(x){ 
        GPIOB->BSRR = GPIO_BSRR_BS0;
    } else { 
        GPIOB->BSRR = GPIO_BSRR_BR0;
    }
}

void ROW7(int x){
    if(x){ 
        GPIOA->BSRR = GPIO_BSRR_BS3;
    } else { 
        GPIOA->BSRR = GPIO_BSRR_BR3;
    }
}

/*
 * Fonction d'attente (sleep) en microsecondes (approximation).
 * Utilise une boucle et l'instruction "nop" pour retarder l'exécution.
 */
static inline void sleep(unsigned int time ){
    for (unsigned int i = 0; i < time; i++){
        asm volatile("nop");
    }
} 

/*
 * Génère une impulsion sur la ligne SCK : passe à 1 puis à 0 avec un délai.
 */
void pulse_SCK(){
    SCK(1);
    sleep(1);
    SCK(0);
}

/*
 * Génère une impulsion sur la ligne LAT (Latch) : inverse l'état puis revient.
 */
void pulse_LAT(){
    Lat(0);
    sleep(1);
    Lat(1);
}

/*
 * Initialise la "bank0" de la matrice.
 * Configure SB et SDA, puis envoie 144 impulsions sur SCK,
 * suivies d'une impulsion sur LAT pour valider.
 */
void init_bank0(){
    SB(0);
    SDA(1);
    for(int i = 0; i < 144; i++){
        pulse_SCK();
    } 
    pulse_LAT();
} 

/*
 * Initialisation de la matrice.
 * Active les horloges pour GPIOA, GPIOB, GPIOC et configure les modes 
 * et la vitesse des broches utilisées par la matrice.
 * Configure ensuite les niveaux initiaux des signaux (RST, Lat, SB, SCK, SDA)
 * et initialise les lignes de la matrice à l'état bas.
 * Un délai est inséré pour laisser le temps au matériel de se stabiliser.
 * Enfin, active le reset et initialise la bank0.
 */
void matrix_init() {
    // Activation des horloges pour GPIOC, GPIOB et GPIOA
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOAEN;

    // Configuration des modes des broches pour GPIOB (ROW, SCK, etc.)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk & ~GPIO_MODER_MODE1_Msk & ~GPIO_MODER_MODE2_Msk)
                     | (GPIO_MODER_MODE0_0) | (GPIO_MODER_MODE1_0) | (GPIO_MODER_MODE2_0);
    
    // Configuration des modes des broches pour GPIOC (RST, LAT, SB)
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk & ~GPIO_MODER_MODE4_Msk & ~GPIO_MODER_MODE5_Msk)
                     | (GPIO_MODER_MODE4_0) | (GPIO_MODER_MODE3_0) | (GPIO_MODER_MODE5_0);
    
    // Configuration des modes des broches pour GPIOA (divers signaux de la matrice)
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk & ~GPIO_MODER_MODE3_Msk
                    & ~GPIO_MODER_MODE4_Msk & ~GPIO_MODER_MODE5_Msk 
                    & ~GPIO_MODER_MODE6_Msk & ~GPIO_MODER_MODE7_Msk 
                    & ~GPIO_MODER_MODE15_Msk)
                    | (GPIO_MODER_MODE2_0) | (GPIO_MODER_MODE3_0)
                    | (GPIO_MODER_MODE4_0) | (GPIO_MODER_MODE5_0)
                    | (GPIO_MODER_MODE6_0) | (GPIO_MODER_MODE7_0)
                    | (GPIO_MODER_MODE15_0);

    // Configuration de la vitesse (OSPEEDR) pour chaque groupe de broches
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk & GPIO_OSPEEDR_OSPEED1_Msk
                     & ~GPIO_OSPEEDR_OSPEED2_Msk)
                     | (3 << GPIO_OSPEEDR_OSPEED0_Pos) | (3 << GPIO_OSPEEDR_OSPEED1_Pos)
                     | (3 << GPIO_OSPEEDR_OSPEED2_Pos);

    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk & GPIO_OSPEEDR_OSPEED4_Msk
                     & ~GPIO_OSPEEDR_OSPEED5_Msk)
                     | (3 << GPIO_OSPEEDR_OSPEED3_Pos) | (3 << GPIO_OSPEEDR_OSPEED4_Pos)
                     | (3 << GPIO_OSPEEDR_OSPEED5_Pos);

    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk & GPIO_OSPEEDR_OSPEED3_Msk
                     & ~GPIO_OSPEEDR_OSPEED4_Msk & ~GPIO_OSPEEDR_OSPEED5_Msk
                     & GPIO_OSPEEDR_OSPEED6_Msk & ~GPIO_OSPEEDR_OSPEED7_Msk
                     & ~GPIO_OSPEEDR_OSPEED15_Msk)
                     | (3 << GPIO_OSPEEDR_OSPEED2_Pos) | (3 << GPIO_OSPEEDR_OSPEED3_Pos)
                     | (3 << GPIO_OSPEEDR_OSPEED4_Pos) | (3 << GPIO_OSPEEDR_OSPEED5_Pos)
                     | (3 << GPIO_OSPEEDR_OSPEED6_Pos) | (3 << GPIO_OSPEEDR_OSPEED7_Pos)
                     | (3 << GPIO_OSPEEDR_OSPEED15_Pos);

    // Initialisation des signaux : mise à l'état initial
    RST(0);
    Lat(1);
    SB(1);      
    SCK(0);
    SDA(0);
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);

    // Délai d'attente (~500 ms) pour stabiliser le système
    for (uint32_t i = 0; i < 40000000; i++){
        asm volatile("nop");
    }
    
    // Active le signal RST et initialise la bank0
    RST(1);
    init_bank0();
    SB(1);
} 

/*
 * Désactive toutes les lignes de la matrice (met à 0 ROW0 à ROW7)
 */
void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

/*
 * Active une ligne spécifique de la matrice en fonction de l'argument 'row'
 */
void activate_row(int row){
    switch(row){
        case 0: 
            ROW0(1);
            break;
        case 1: 
            ROW1(1);
            break;
        case 2: 
            ROW2(1);
            break;
        case 3: 
            ROW3(1);
            break;
        case 4: 
            ROW4(1);
            break;
        case 5: 
            ROW5(1);
            break;
        case 6: 
            ROW6(1);
            break;
        case 7: 
            ROW7(1);
            break;
        default: 
            deactivate_rows();
            break;
    }
}

/*
 * Envoie un octet sur la ligne SDA bit par bit.
 * Pour chaque bit, on envoie la valeur (0 ou 1) et on génère une impulsion sur SCK.
 */
void send_byte(uint8_t val){
    for(int i = 0; i < 8; i++){
        SDA(val & (1 << (7 - i)));  // Envoie le bit le plus significatif en premier
        pulse_SCK();
    }
}

/*
 * Configure une ligne de la matrice pour afficher 8 pixels.
 * Pour chaque pixel, les couleurs sont envoyées dans l'ordre : bleu, vert, rouge.
 * Une impulsion sur LAT valide l'envoi de la ligne.
 */
void mat_set_row(int row, const rgb_color *val){
    activate_row(row);
    for (int i = 0; i < 8; i++){
        send_byte(val[i].b);
        send_byte(val[i].g);
        send_byte(val[i].r);
    } 
    pulse_LAT();
} 

/*
 * Test des pixels : boucle infinie affichant successivement
 * les dégradés bleu, rouge et vert sur les lignes de la matrice.
 */
void test_pixels(){
    while(1){
        // Initialisation des dégradés
        degrade_bleu_init();
        degrade_vert_init();
        degrade_rouge_init();

        // Pointeurs sur les tableaux de dégradé
        rgb_color *ptb = &dbleu[0];
        rgb_color *ptr = &drouge[0];
        rgb_color *ptv = &dvert[0];

        // Affichage du dégradé bleu ligne par ligne avec délai
        for(int i = 0; i < 8; i++){
            rgb_color *intermed = ptb;
            mat_set_row(i, intermed);
            sleep(10000);
        }
        deactivate_rows();

        // Affichage du dégradé rouge
        for(int i = 0; i < 8; i++){
            rgb_color *intermed = ptr;
            mat_set_row(i, intermed);
            sleep(10000);
        }
        deactivate_rows();

        // Affichage du dégradé vert
        for(int i = 0; i < 8; i++){
            rgb_color *intermed = ptv;
            mat_set_row(i, intermed);
            sleep(10000);
        }
        deactivate_rows();
    } 
}

/*
 * Test statique des pixels : lit l'image binaire intégrée et affiche chaque ligne.
 * Pour chaque ligne, lit 8 pixels (chaque pixel est composé de 3 octets : r, g, b)
 * et appelle mat_set_row pour l'affichage.
 */
void test_static(){
    while(1){
        rgb_color coleur_ligne[8];
        uint8_t *pt = &_binary_image_raw_start;
        // Parcours de 8 lignes
        for(int i = 0; i < 8; i++) {
            rgb_color *cpt = &coleur_ligne[0];
            // Pour chaque ligne, lit 8 pixels (24 octets)
            for(int i = 0; i < 8; i++){
                cpt->r = *pt; 
                pt++;
                cpt->g = *pt;
                pt++;
                cpt->b = *pt;
                pt++;
                cpt++;
            }
            cpt = &coleur_ligne[0];
            mat_set_row(i, cpt);
            deactivate_rows();
        }
    }
}

/*
 * Affiche la trame globale sur la matrice.
 * La trame est parcourue à l'envers et envoyée par groupes de 3 octets pour chaque pixel.
 * Une impulsion sur LAT est générée, puis la ligne correspondante est activée avec un délai.
 */
void afficher_trame(){
    while(1){
        // Pointeur sur la fin de la trame
        uint8_t *trame_fin = (uint8_t *)&trame_global[191];
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                send_byte(*trame_fin);
                trame_fin--;
                send_byte(*trame_fin);
                trame_fin--;
                send_byte(*trame_fin);
                trame_fin--;
            }
            pulse_LAT();
            activate_row(7 - i);
            sleep(200);
            deactivate_rows();
        } 
    }
}

/*
 * Initialisation de la trame globale.
 * Copie les données de l'image binaire (_binary_image_raw_start) dans trame_global.
 */
void init_tram(){
    uint8_t *trame_depart = &trame_global[0];
    uint8_t *pt_data = &_binary_image_raw_start;
    for(int i = 0; i < 192; i++){
        *trame_depart = *pt_data;
        trame_depart++;
        pt_data++;
    }
}
