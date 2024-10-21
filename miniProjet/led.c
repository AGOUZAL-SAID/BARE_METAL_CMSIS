#include "led.h" 
#include "stm32l475xx.h"


#define REG_GPIOB_MODER    (*(volatile int *) 0x48000400) 
#define B_REG_BSRR         (*(volatile int *) 0x48000418)      
#define REG_GPIOC_MODER    (*(volatile int *) 0x48000800)
#define REG_BSRR_C         (*(volatile int *) 0x48000818)
#define REG_RCC_AHB2ENR    (*(volatile int *) 0x4002104c)  


void led_init(void){
    RCC->AHB2ENR   = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN ;
    GPIOB->MODER =  (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | (GPIO_MODER_MODE14_0);
}  

void led_g_on(){
    GPIOB ->BSRR       = GPIO_BSRR_BS14;
} 

void led_g_off(){
    GPIOB ->BSRR       = GPIO_BSRR_BR14 ;
}

void led(enum state comand){
    if (comand == LED_YELLOW ){
        GPIOC->MODER           = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | (GPIO_MODER_MODE9_0) ;
        GPIOC->BSRR                = GPIO_BSRR_BS9;
    } 
    if (comand == LED_BLUE){
        GPIOC->MODER           = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | (GPIO_MODER_MODE9_0);
        REG_BSRR_C                = GPIO_BSRR_BR9;
    }  
    if(comand == LED_OFF)
        REG_GPIOC_MODER          = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) ;
    } 

/*   
la fonction sleep prend un nombre entier qui represant le temps en ms
*/

void sleep(unsigned int time ){
    unsigned int k = time * 4000;
    for (unsigned int i = 0; i<k; i++){
        asm volatile("nop");
        }
} 