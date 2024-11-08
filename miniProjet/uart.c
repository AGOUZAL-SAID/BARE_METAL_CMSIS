#include "stm32l475xx.h"

typedef unsigned int size_t;

void uart_init(int baudrate){
    USART1 ->CR1     =  (USART1 ->CR1   & ~USART_CR1_UE_Msk);

    RCC  ->AHB2ENR   =   RCC->AHB2ENR   | RCC_AHB2ENR_GPIOBEN;

    GPIOB->MODER     =  (GPIOB->MODER   & ~GPIO_MODER_MODE6_Msk)        | (2 << GPIO_MODER_MODE6_Pos)         ;
    
    GPIOB->MODER     =  (GPIOB->MODER   & ~GPIO_MODER_MODE7_Msk)        | (2 << GPIO_MODER_MODE7_Pos)         ;                                            
    
    GPIOB->AFR[0]    =  (GPIOB->AFR[0]  & ~GPIO_AFRL_AFSEL6_Msk)        | (7<<GPIO_AFRL_AFSEL6_Pos)     ;
    
    GPIOB->AFR[0]    =  (GPIOB->AFR[0]  & ~GPIO_AFRL_AFSEL7_Msk)        | (7<<GPIO_AFRL_AFSEL7_Pos)     ;
    
    RCC  ->APB2ENR   =  (RCC  ->APB2ENR & ~RCC_APB2ENR_USART1EN_Msk)    | (1<<RCC_APB2ENR_USART1EN_Pos) ;
    
    RCC  ->CCIPR     =  (RCC  ->CCIPR   & ~RCC_CCIPR_USART1SEL_Msk)                                     ;  
    
    RCC  ->APB2RSTR  =  (RCC  ->APB2RSTR& ~RCC_APB2RSTR_USART1RST_Msk ) | (1<<RCC_APB2RSTR_USART1RST_Pos);
    
    RCC  ->APB2RSTR  =  (RCC  ->APB2RSTR& ~RCC_APB2RSTR_USART1RST_Msk )                                  ;

    USART1->BRR      =  (USART1 -> BRR  & ~USART_BRR_DIV_FRACTION_Msk   & ~USART_BRR_DIV_MANTISSA_Msk) | ((80000000/baudrate) << USART_BRR_DIV_FRACTION_Pos);
    
    USART1->CR1      =  0                                                                               ;
    
    USART1 ->CR2     =  (USART1->CR2    & ~USART_CR2_STOP_Msk)                                           ;
    
    USART1 ->CR1     =  (USART1 ->CR1   & ~USART_CR1_UE_Msk)            | (USART_CR1_UE)                 ;
    
    USART1 ->CR1     =  (USART1 ->CR1   & ~USART_CR1_TE_Msk)            | (USART_CR1_TE)                 ;
    
    USART1 ->CR1     =  (USART1 ->CR1   & ~USART_CR1_RE_Msk)            | (USART_CR1_RE)                 ;

} 

void uart_putchar(uint8_t c){
    while(1)
    {
        if (USART1->ISR & USART_ISR_TXE)
        {
            USART1->TDR = (USART1->TDR & ~USART_TDR_TDR_Msk)| (c<<USART_TDR_TDR_Pos);
            break;   
        } 
    }         
} 

uint8_t uart_getchar(){
    while(1){
        if(USART1 ->ISR & USART_ISR_RXNE){
            return (uint8_t) (USART1->RDR & USART_RDR_RDR_Msk) ;
        } 
    } 
} 


void uart_puts(const char *s){
    uint32_t i =0 ; 
    while(1)
    {
        
        if(s[i]=='\0'){break;}
        
        else
        {
            uart_putchar((uint8_t)s[i] );
            i++;
        }  
    }
    uart_putchar((uint8_t)'\r');
    uart_putchar((uint8_t)'\n');
    uart_putchar((uint8_t)'\0');
}


void uart_gets(char *s, size_t size){
    char * word = s;
    uint32_t i =0 ; 
    while(i<((uint32_t)size)-1){
        *word = uart_getchar();
        word++;
        i++;
    } 
    *word = '\0';
} 

uint32_t uart_calculate (uint32_t n ){
    uint32_t somme = 0 ;
    for (uint32_t i = 0 ;i<n;i++ ){
        uint8_t word = uart_getchar();
        somme += word ; 
    }
    return somme;
}