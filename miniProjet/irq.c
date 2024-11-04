#include "stm32l475xx.h"
#include "system_stm32l4xx.h"
#include "core_cm4.h"
#include "irq.h"




extern uint32_t _stack;
extern uint32_t _start;
#define MAKE_DEFAULT_HANDLER(truc_IRQHandler) \
    void __attribute__((weak)) (truc_IRQHandler)(void) { \
        __disable_irq();  \
        while(1); \
    }


MAKE_DEFAULT_HANDLER(NMI_Handler);
MAKE_DEFAULT_HANDLER(HardFault_Handler);
MAKE_DEFAULT_HANDLER(MemManage_Handler);
MAKE_DEFAULT_HANDLER(BusFault_Handler);
MAKE_DEFAULT_HANDLER(UsageFault_Handler);
MAKE_DEFAULT_HANDLER(SVC_Handler);
MAKE_DEFAULT_HANDLER(DebugMon_Handler);
MAKE_DEFAULT_HANDLER(PendSV_Handler);
MAKE_DEFAULT_HANDLER(SysTick_Handler);
MAKE_DEFAULT_HANDLER(WWDG_IRQHandler);
MAKE_DEFAULT_HANDLER(PVD_PVM_IRQHandler);
MAKE_DEFAULT_HANDLER(TAMP_STAMP_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC_WKUP_IRQHandler);
MAKE_DEFAULT_HANDLER(FLASH_IRQHandler);
MAKE_DEFAULT_HANDLER(RCC_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI0_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI1_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI2_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI3_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler);
MAKE_DEFAULT_HANDLER(ADC1_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_TX_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_RX0_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_RX1_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_SCE_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI9_5_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_BRK_TIM15_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_UP_TIM16_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_TRG_COM_TIM17_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_CC_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM2_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM3_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM4_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C1_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C1_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C2_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C2_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI2_IRQHandler);
MAKE_DEFAULT_HANDLER(USART1_IRQHandler);
MAKE_DEFAULT_HANDLER(USART2_IRQHandler);
MAKE_DEFAULT_HANDLER(USART3_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI15_10_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC_Alarm_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT3_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_BRK_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_UP_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_TRG_COM_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_CC_IRQHandler);
MAKE_DEFAULT_HANDLER(ADC3_IRQHandler);
MAKE_DEFAULT_HANDLER(FMC_IRQHandler);
MAKE_DEFAULT_HANDLER(SDMMC1_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM5_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI3_IRQHandler);
MAKE_DEFAULT_HANDLER(UART4_IRQHandler);
MAKE_DEFAULT_HANDLER(UART5_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM6_DAC_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM7_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel3_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel5_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT0_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT1_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT2_IRQHandler);
MAKE_DEFAULT_HANDLER(COMP_IRQHandler);
MAKE_DEFAULT_HANDLER(LPTIM1_IRQHandler);
MAKE_DEFAULT_HANDLER(LPTIM2_IRQHandler);
MAKE_DEFAULT_HANDLER(OTG_FS_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel6_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel7_IRQHandler);
MAKE_DEFAULT_HANDLER(LPUART1_IRQHandler);
MAKE_DEFAULT_HANDLER(QUADSPI_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C3_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C3_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(SAI1_IRQHandler);
MAKE_DEFAULT_HANDLER(SAI2_IRQHandler);
MAKE_DEFAULT_HANDLER(SWPMI1_IRQHandler);
MAKE_DEFAULT_HANDLER(TSC_IRQHandler);
MAKE_DEFAULT_HANDLER(RNG_IRQHandler);
MAKE_DEFAULT_HANDLER(FPU_IRQHandler);


void * const vector_table[] __attribute__((aligned(512))) = {
    // Pile et Reset Handler
    &_stack,                         // Sommet de la pile (SP initial)
    &_start,                          // Handler de Reset (PC initial)

    // Exceptions internes ARM Cortex-M4
    NMI_Handler,                     // NMI handler
    HardFault_Handler,               // Hard Fault handler
    MemManage_Handler,               // Memory Management Fault handler
    BusFault_Handler,                // Bus Fault handler
    UsageFault_Handler,              // Usage Fault handler
    0,                               // Réservé
    0,                               // Réservé
    0,                               // Réservé
    0,                               // Réservé
    SVC_Handler,                     // SVC handler
    DebugMon_Handler,                // Debug Monitor handler
    0,                               // Réservé
    PendSV_Handler,                  // Pending SVC handler
    SysTick_Handler,                 // SysTick handler

    // Interruptions externes STM32L475
    WWDG_IRQHandler,                 // Watchdog IRQ handler
    PVD_PVM_IRQHandler,              // PVD/PVM IRQ handler
    TAMP_STAMP_IRQHandler,           // Tamper and TimeStamp IRQ handler
    RTC_WKUP_IRQHandler,             // RTC Wakeup IRQ handler
    FLASH_IRQHandler,                // Flash IRQ handler
    RCC_IRQHandler,                  // RCC IRQ handler
    EXTI0_IRQHandler,                // EXTI Line 0 IRQ handler
    EXTI1_IRQHandler,                // EXTI Line 1 IRQ handler
    EXTI2_IRQHandler,                // EXTI Line 2 IRQ handler
    EXTI3_IRQHandler,                // EXTI Line 3 IRQ handler
    EXTI4_IRQHandler,                // EXTI Line 4 IRQ handler
    DMA1_Channel1_IRQHandler,        // DMA1 Channel 1 IRQ handler
    DMA1_Channel2_IRQHandler,        // DMA1 Channel 2 IRQ handler
    DMA1_Channel3_IRQHandler,        // DMA1 Channel 3 IRQ handler
    DMA1_Channel4_IRQHandler,        // DMA1 Channel 4 IRQ handler
    DMA1_Channel5_IRQHandler,        // DMA1 Channel 5 IRQ handler
    DMA1_Channel6_IRQHandler,        // DMA1 Channel 6 IRQ handler
    DMA1_Channel7_IRQHandler,        // DMA1 Channel 7 IRQ handler
    ADC1_IRQHandler,                 // ADC1 IRQ handler
    CAN1_TX_IRQHandler,              // CAN1 TX IRQ handler
    CAN1_RX0_IRQHandler,             // CAN1 RX0 IRQ handler
    CAN1_RX1_IRQHandler,             // CAN1 RX1 IRQ handler
    CAN1_SCE_IRQHandler,             // CAN1 SCE IRQ handler
    EXTI9_5_IRQHandler,              // EXTI Line[9:5] IRQ handler
    TIM1_BRK_TIM15_IRQHandler,       // TIM1 Break and TIM15 IRQ handler
    TIM1_UP_TIM16_IRQHandler,        // TIM1 Update and TIM16 IRQ handler
    TIM1_TRG_COM_TIM17_IRQHandler,   // TIM1 Trigger/Commutation and TIM17 IRQ handler
    TIM1_CC_IRQHandler,              // TIM1 Capture Compare IRQ handler
    TIM2_IRQHandler,                 // TIM2 IRQ handler
    TIM3_IRQHandler,                 // TIM3 IRQ handler
    TIM4_IRQHandler,                 // TIM4 IRQ handler
    I2C1_EV_IRQHandler,              // I2C1 Event IRQ handler
    I2C1_ER_IRQHandler,              // I2C1 Error IRQ handler
    I2C2_EV_IRQHandler,              // I2C2 Event IRQ handler
    I2C2_ER_IRQHandler,              // I2C2 Error IRQ handler
    SPI1_IRQHandler,                 // SPI1 IRQ handler
    SPI2_IRQHandler,                 // SPI2 IRQ handler
    USART1_IRQHandler,               // USART1 IRQ handler
    USART2_IRQHandler,               // USART2 IRQ handler
    USART3_IRQHandler,               // USART3 IRQ handler
    EXTI15_10_IRQHandler,            // EXTI Line[15:10] IRQ handler
    RTC_Alarm_IRQHandler,            // RTC Alarm IRQ handler
    DFSDM1_FLT3_IRQHandler,          // DFSDM1 Filter 3 IRQ handler
    TIM8_BRK_IRQHandler,             // TIM8 Break IRQ handler
    TIM8_UP_IRQHandler,              // TIM8 Update IRQ handler
    TIM8_TRG_COM_IRQHandler,         // TIM8 Trigger/Commutation IRQ handler
    TIM8_CC_IRQHandler,              // TIM8 Capture Compare IRQ handler
    ADC3_IRQHandler,                 // ADC3 IRQ handler
    FMC_IRQHandler,                  // FMC IRQ handler
    SDMMC1_IRQHandler,               // SDMMC1 IRQ handler
    TIM5_IRQHandler,                 // TIM5 IRQ handler
    SPI3_IRQHandler,                 // SPI3 IRQ handler
    UART4_IRQHandler,                // UART4 IRQ handler
    UART5_IRQHandler,                // UART5 IRQ handler
    TIM6_DAC_IRQHandler,             // TIM6 and DAC IRQ handler
    TIM7_IRQHandler,                 // TIM7 IRQ handler
    DMA2_Channel1_IRQHandler,        // DMA2 Channel 1 IRQ handler
    DMA2_Channel2_IRQHandler,        // DMA2 Channel 2 IRQ handler
    DMA2_Channel3_IRQHandler,        // DMA2 Channel 3 IRQ handler
    DMA2_Channel4_IRQHandler,        // DMA2 Channel 4 IRQ handler
    DMA2_Channel5_IRQHandler,        // DMA2 Channel 5 IRQ handler
    DFSDM1_FLT0_IRQHandler,          // DFSDM1 Filter 0 IRQ handler
    DFSDM1_FLT1_IRQHandler,          // DFSDM1 Filter 1 IRQ handler
    DFSDM1_FLT2_IRQHandler,          // DFSDM1 Filter 2 IRQ handler
    COMP_IRQHandler,                 // COMP IRQ handler
    LPTIM1_IRQHandler,               // LPTIM1 IRQ handler
    LPTIM2_IRQHandler,               // LPTIM2 IRQ handler
    OTG_FS_IRQHandler,               // OTG FS IRQ handler
    DMA2_Channel6_IRQHandler,        // DMA2 Channel 6 IRQ handler
    DMA2_Channel7_IRQHandler,        // DMA2 Channel 7 IRQ handler
    LPUART1_IRQHandler,              // LPUART1 IRQ handler
    QUADSPI_IRQHandler,              // QUADSPI IRQ handler
    I2C3_EV_IRQHandler,              // I2C3 Event IRQ handler
    I2C3_ER_IRQHandler,              // I2C3 Error IRQ handler
    SAI1_IRQHandler,                 // SAI1 IRQ handler
    SAI2_IRQHandler,                 // SAI2 IRQ handler
    SWPMI1_IRQHandler,               // SWPMI1 IRQ handler
    TSC_IRQHandler,                  // TSC IRQ handler
    RNG_IRQHandler,                  // RNG IRQ handler
    FPU_IRQHandler,                  // FPU IRQ handler
};



void irq_init(){
    SCB->VTOR = (SCB->VTOR & ~(SCB_VTOR_TBLOFF_Msk)) | ((uint32_t)vector_table) ;
}

