#include "stm32l475xx.h"
#include "buttons.h"
#ifndef A_0
#define A_0
#include "led.h"
#endif
void button_init() {
    RCC->AHB2ENR       =    RCC->AHB2ENR |  RCC_AHB2ENR_GPIOCEN                                                 ;
    GPIOC->MODER       =   (GPIOC->MODER & ~GPIO_MODER_MODE13_Msk)                                              ;
    SYSCFG->EXTICR[3]  =   (SYSCFG->EXTICR[3] & ~(SYSCFG_EXTICR4_EXTI13)) | (2 << SYSCFG_EXTICR4_EXTI13_Pos)    ; 
    EXTI->IMR1         =   (EXTI->IMR1        & ~(EXTI_IMR1_IM13_Msk))    | (1 << EXTI_IMR1_IM13_Pos)           ;
    EXTI->RTSR1        =   (EXTI->RTSR1       & ~(EXTI_RTSR1_RT13_Msk)) ;
    EXTI->FTSR1        =   (EXTI->FTSR1       & ~(EXTI_FTSR1_FT13_Msk))   | ( 1<< EXTI_FTSR1_FT13_Pos )         ;
    NVIC_EnableIRQ(40)                                                                                          ;
}


void EXTI15_10_IRQHandler(void) { 

        static uint8_t etat = 0;
        
        for (unsigned int i = 0; i<20000; i++){asm volatile("nop");}

        if(etat ==0){
            led_g_on();
            etat=1;}
        
        else{
            led_g_off();
            etat=0;
        }    
        
        EXTI->PR1 = (EXTI->PR1 & ~(EXTI_PR1_PIF13_Msk)) |  (1<<EXTI_PR1_PIF13_Pos);
        
        }