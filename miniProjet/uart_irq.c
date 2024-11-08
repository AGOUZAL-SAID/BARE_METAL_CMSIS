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
    if(~(USART1->ISR & USART_ISR_FE_Msk) & ~(USART1->ISR & USART_ISR_ORE_Msk)){
        if((data == 0xff) | (position_in_trame == 192)){
            trame_depart = &trame_global[0] ;
            position_in_trame=0;
        }
        else{
            *trame_depart=data;
            trame_depart++;
            position_in_trame++;}    
    }
    else{
        if(data == 0xff ){
            trame_depart = &trame_global[0] ;
            position_in_trame=0;
            USART1->ICR = (USART1->ICR &~(USART_ICR_FECF_Msk)) | (1<<USART_ICR_FECF_Pos); 
            USART1->ICR = (USART1->ICR &~(USART_ICR_ORECF_Msk)) | (1<<USART_ICR_ORECF_Pos);
        }
    }
    }
  
    

void enable_interruption_uart(){
    USART1->CR1 = (USART1->CR1 & ~(USART_CR1_RXNEIE_Msk)) | ( 1<< USART_CR1_RXNEIE_Pos ) ; 
    NVIC_EnableIRQ(37) ;
}
