#include "led.h" 


#define REG_GPIOB_MODER    (*(volatile int *) 0x48000400) 
#define B_REG_BSRR         (*(volatile int *) 0x48000418)      
#define REG_GPIOC_MODER    (*(volatile int *) 0x48000800)
#define REG_BSRR_C         (*(volatile int *) 0x48000818)    
#define REG_RCC_AHB2ENR    (*(volatile int *) 0x4002104c)  


void led_init(void){
    REG_RCC_AHB2ENR    = REG_RCC_AHB2ENR | (1 << 2) | (1 << 1) ;
    REG_GPIOB_MODER    =  (1 << 28);
}  

void led_g_on(){
    B_REG_BSRR         = (1 << 14);
} 

void led_g_off(){
    B_REG_BSRR         = (1 << 30) ;
}

void led(enum state comand){
    if (comand == LED_YELLOW ){
        REG_GPIOC_MODER           = REG_GPIOC_MODER | (1 << 18);
        REG_BSRR_C                = (1 << 9);
    } 
    if (comand == LED_BLUE){
        REG_GPIOC_MODER           = REG_GPIOC_MODER | (1 << 18);
        REG_BSRR_C                = (1 << (9+16));
    }  
    if(comand == LED_OFF)
        REG_GPIOC_MODER          &= ~(0x3 << 18); ;
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