#include "uart.h"
#include "uart_irq.h"
#include "stm32l475xx.h"
#include "system_stm32l4xx.h"
#include "core_cm4.h"
extern uint8_t trame_global[192];
uint8_t * trame_depart = &trame_global[0];
static uint8_t   position_in_trame = 0;

void USART1_IRQHandler(void) {
    uint8_t data = uart_getchar();
    if((data == 0xff) | (position_in_trame == 192)){
            trame_depart = &trame_global[0] ;
            position_in_trame=0;
        }
    else{
        *trame_depart=data;
        trame_depart++;
        position_in_trame++;}    
    }  
    

void enable_interruption_uart(){
    USART1->CR1 = (USART1->CR1 & ~(USART_CR1_RXNEIE_Msk)) | ( 1<< USART_CR1_RXNEIE_Pos ) ; 
    NVIC_EnableIRQ(37) ;
}
void init_tram(){
    for(int i =0;i<192;i++){
        *trame_depart = 0;
        trame_depart++;
    }
    trame_depart=&trame_global[0];
}