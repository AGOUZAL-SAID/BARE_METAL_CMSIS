#include "stm32l475xx.h"
#include "matrix.h"

extern uint8_t _binary_image_raw_start;
extern uint8_t _binary_image_raw_end;
extern uint8_t _binary_image_raw_size;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
}   rgb_color;
rgb_color dbleu [8];
rgb_color drouge[8];
rgb_color dvert [8];

void degrade_bleu_init(){
    uint8_t b = 5;
    rgb_color * pt =  &dbleu[0]; 
    for(int i=0;i<8;i++){
        pt->r = 0 ;
        pt->g = 0 ;
        pt->b = b ;
        pt++;
        b =30*(i+2);
    } 
} 

void degrade_rouge_init(){
    uint8_t b = 5;
    rgb_color * pt =  &drouge[0]; 
    for(int i=0;i<8;i++){
        pt->r = b ;
        pt->g = 0 ;
        pt->b = 0 ;
        pt++;
        b=30*(i+2);
    } 
} 

void degrade_vert_init(){
    uint8_t b = 5;
    rgb_color * pt =  &dvert[0]; 
    for(int i=0;i<8;i++){    
        pt->r = 0  ;
        pt->g = b  ;
        pt->b = 0  ;
        pt++       ;
        b = 30*(i+2) ; 
    } 
} 

void RST(int x){
    if(x){GPIOC ->BSRR   =  GPIO_BSRR_BS3;}
    else {GPIOC ->BSRR   =  GPIO_BSRR_BR3;}

} 

void SB(int x){
    if(x){GPIOC ->BSRR  =  GPIO_BSRR_BS5;}
    else {GPIOC ->BSRR  =  GPIO_BSRR_BR5;}

}

void Lat(int x){
    if(x){GPIOC ->BSRR  =  GPIO_BSRR_BS4;}
    else {GPIOC ->BSRR  =  GPIO_BSRR_BR4;}

}

void SCK(int x){
    if(x){GPIOB ->BSRR  =  GPIO_BSRR_BS1;}
    else {GPIOB ->BSRR  =  GPIO_BSRR_BR1;}
}

void SDA(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS4;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR4;}
    }

void ROW0(int x){
    if(x){GPIOB ->BSRR  =  GPIO_BSRR_BS2;}
    else {GPIOB ->BSRR  =  GPIO_BSRR_BR2;}
}

void ROW1(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS15;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR15;}
}

void ROW2(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS2;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR2;}
}

void ROW3(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS7;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR7;}
}

void ROW4(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS6;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR6;}
}

void ROW5(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS5;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR5;}
}

void ROW6(int x){
    if(x){GPIOB ->BSRR  =  GPIO_BSRR_BS0;}
    else {GPIOB ->BSRR  =  GPIO_BSRR_BR0;}
}

void ROW7(int x){
    if(x){GPIOA ->BSRR  =  GPIO_BSRR_BS3;}
    else {GPIOA ->BSRR  =  GPIO_BSRR_BR3;}
}

/*
la fonction sleep force le processeur a ne rien faire pendant un temps "time" en us 
*/
void sleep(unsigned int time ){
    unsigned int k = time * 30;
    for (unsigned int i = 0; i<k; i++){
        asm volatile("nop");
        }
} 

void pulse_SCK(){
    SCK(0);
    sleep(1);
    SCK(1);
    sleep(1);
    SCK(0);
    sleep(1);
}

void pulse_LAT(){
    Lat(1);
    sleep(1);
    Lat(0);
    sleep(1);
    Lat(1);
    sleep(1);
}
void init_bank0(){
    SB(0);
    for(int i = 0 ; i<144 ;i++){
        SDA(1);
        pulse_SCK();
    } 
    pulse_LAT();
} 
void matrix_init() {
    RCC->AHB2ENR   =   RCC  ->AHB2ENR | RCC_AHB2ENR_GPIOCEN   | RCC_AHB2ENR_GPIOBEN |RCC_AHB2ENR_GPIOAEN       ;
    GPIOB->MODER   =  (GPIOB->MODER   & ~GPIO_MODER_MODE0_Msk & ~GPIO_MODER_MODE1_Msk &~GPIO_MODER_MODE2_Msk ) | (GPIO_MODER_MODE0_0) | (GPIO_MODER_MODE1_0) | (GPIO_MODER_MODE2_0);
    GPIOC->MODER   =  (GPIOC->MODER   & ~GPIO_MODER_MODE3_Msk &~GPIO_MODER_MODE4_Msk  &~GPIO_MODER_MODE5_Msk)  |  (GPIO_MODER_MODE4_0) | (GPIO_MODER_MODE3_0)| (GPIO_MODER_MODE5_0);
    GPIOA->MODER   =  (GPIOA->MODER   & ~GPIO_MODER_MODE2_Msk &~GPIO_MODER_MODE3_Msk  &~GPIO_MODER_MODE4_Msk & ~GPIO_MODER_MODE5_Msk &~GPIO_MODER_MODE6_Msk  &~GPIO_MODER_MODE7_Msk &~GPIO_MODER_MODE15_Msk)  |  (GPIO_MODER_MODE2_0) | (GPIO_MODER_MODE3_0)| (GPIO_MODER_MODE4_0) |(GPIO_MODER_MODE5_0) | (GPIO_MODER_MODE6_0) | (GPIO_MODER_MODE7_0) |  (GPIO_MODER_MODE15_0);
    GPIOB->OSPEEDR =  (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk & GPIO_OSPEEDR_OSPEED1_Msk & ~GPIO_OSPEEDR_OSPEED2_Msk ) | (3<<GPIO_OSPEEDR_OSPEED0_Pos) | (3<<GPIO_OSPEEDR_OSPEED1_Pos) | (3<<GPIO_OSPEEDR_OSPEED2_Pos) ;
    GPIOC->OSPEEDR =  (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk & GPIO_OSPEEDR_OSPEED4_Msk & ~GPIO_OSPEEDR_OSPEED5_Msk ) | (3<<GPIO_OSPEEDR_OSPEED3_Pos) | (3<<GPIO_OSPEEDR_OSPEED4_Pos) | (3<<GPIO_OSPEEDR_OSPEED5_Pos) ;
    GPIOA->OSPEEDR =  (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk & GPIO_OSPEEDR_OSPEED3_Msk & ~GPIO_OSPEEDR_OSPEED4_Msk & ~GPIO_OSPEEDR_OSPEED5_Msk & GPIO_OSPEEDR_OSPEED6_Msk & ~GPIO_OSPEEDR_OSPEED7_Msk & ~GPIO_OSPEEDR_OSPEED15_Msk) | (3<<GPIO_OSPEEDR_OSPEED2_Pos) | (3<<GPIO_OSPEEDR_OSPEED3_Pos) | (3<<GPIO_OSPEEDR_OSPEED4_Pos)| (3<<GPIO_OSPEEDR_OSPEED5_Pos) | (3<<GPIO_OSPEEDR_OSPEED6_Pos) | (3<<GPIO_OSPEEDR_OSPEED7_Pos) | (3<<GPIO_OSPEEDR_OSPEED15_Pos)  ;
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
    for (uint32_t i =0 ; i<40000000 ;i++){asm volatile("nop");} // delay de 500 ms
    RST(1);
    init_bank0();
    SB(1);

} 


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

void activate_row(int row){
    switch(row){
        case 0 : 
            ROW0(1);
            break;
        case 1 : 
            ROW1(1);
            break;
        case 2 : 
            ROW2(1);
            break;
        case 3 : 
            ROW3(1);
            break;
        case 4 : 
            ROW4(1);
            break;
        case 5 : 
            ROW5(1);
            break;
        case 6 : 
            ROW6(1);
            break;
        case 7 : 
            ROW7(1);
            break;
        default : 
            deactivate_rows();
            break;
    }
}

void send_byte(uint8_t val){
    for(int i =0 ; i<8;i++){
        SDA(val & (1<<(7-i)));
        pulse_SCK();
    }
}

void mat_set_row(int row, const rgb_color *val){
        activate_row(row);
    for (int i=0; i<8 ; i++){
        send_byte(val->b);
        send_byte(val->g);
        send_byte(val->r);
        val++;
    } 
    pulse_LAT();
} 

void test_pixels(){
    while(1){
        degrade_bleu_init()           ;
        degrade_vert_init()           ;
        degrade_rouge_init()          ;
        rgb_color * ptb =  &dbleu[0]  ;
        rgb_color * ptr =  &drouge[0] ;
        rgb_color * ptv =  &dvert[0]  ;
        for(int i=0 ; i<8;i++){
            rgb_color * intermed = ptb;
            mat_set_row(i, intermed);
            sleep(10000);      
        }  
        deactivate_rows();
        for(int i=0 ; i<8;i++){
            rgb_color * intermed = ptr;
            mat_set_row(i, intermed);
            sleep(10000);      
        }  
        deactivate_rows();
        for(int i=0 ; i<8;i++){
            rgb_color * intermed = ptv;
            mat_set_row(i, intermed);
            sleep(10000);      
        }     
        deactivate_rows();
    } 
}

void test_static(){
    while(1){
        rgb_color coleur_ligne[8];
        uint8_t * pt = &_binary_image_raw_start;
        for(int i = 0 ; i<8 ; i++) {
            rgb_color * cpt = &coleur_ligne[0];
            for(int i=0; i<8;i++){
                cpt->r = *pt ; 
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
}}