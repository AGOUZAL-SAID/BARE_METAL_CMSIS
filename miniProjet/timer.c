#include "stm32l475xx.h"
#include "system_stm32l4xx.h"
#include "core_cm4.h"
#include "led.h"
#include "matrix.h"
#include "time.h"
extern uint8_t trame_global[192];
void timer_init(int max_us)
{
    RCC->APB1ENR1 = (RCC->APB1ENR1 & ~(RCC_APB1ENR1_TIM2EN_Msk)) | (1 << RCC_APB1ENR1_TIM2EN_Pos);
    TIM2->SR = (TIM2->SR & ~(TIM_SR_UIF_Msk));
    TIM2->CNT = (TIM2->CNT & ~(TIM_CNT_CNT_Msk));
    TIM2->CR1 = (TIM2->CR1 & ~(TIM_CR1_CMS_Msk) & ~(TIM_CR1_DIR_Msk));
    TIM2->PSC = (TIM2->PSC & ~(TIM_PSC_PSC_Msk)) | (79 << TIM_PSC_PSC_Pos);
    TIM2->ARR = (TIM2->ARR & ~(TIM_ARR_ARR_Msk)) | (max_us << TIM_ARR_ARR_Pos);
    TIM2->DIER = (TIM2->DIER & ~(TIM_DIER_UIE_Msk)) | (1 << TIM_DIER_UIE_Pos);
    NVIC_EnableIRQ(28);
    TIM2->CR1 = (TIM2->CR1 & ~(TIM_CR1_CEN_Msk)) | (1 << TIM_CR1_CEN_Pos);
}

static int count_time = 0;
static int ligne = 0;
static const int mSecond = 1;
static uint8_t *trame_timer_end = &trame_global[191];

void TIM2_IRQHandler(void){
    TIM2->SR = (TIM2->SR & ~(TIM_SR_UIF_Msk));
    if (count_time != mSecond)
    {
        count_time++;
        return;
    }

    count_time = 0;
    
    deactivate_rows();
    if (ligne == 8)
    {
        trame_timer_end = &trame_global[191];
        ligne = 0;
    }
    for (int j = 0; j < 24; j++)
    {
        send_byte(*trame_timer_end--);
    }
    pulse_LAT();
    activate_row(7-ligne);
    ligne++;
}

