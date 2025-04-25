#include "stm32l475xx.h"
#include "clocks.h"

void clocks_init(void) {
    // PWR clock enable
    RCC->APB1ENR1 = RCC_APB1ENR1_PWREN;

    // Reset BKP domain if different clock source selected
    RCC->BDCR = RCC_BDCR_BDRST;
    RCC->BDCR = 0;

    // Backup domain deprotection
    PWR->CR1 |= PWR_CR1_DBP;

    // MSIRANGE can be set only when MSI is OFF or READY
    RCC->CR = RCC_CR_MSION;
    // Wait until MSI is stable
    while ((RCC->CR & RCC_CR_MSIRDY) == 0) ;

    // Clocking from MSI, in case MSI was not the default source
    RCC->CFGR = 0;
    // Wait until MSI is selected and stable
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI) ;

    // LSE activation, no LSE Bypass
    RCC->BDCR |= RCC_BDCR_LSEDRV_0 | RCC_BDCR_LSEDRV_1 | RCC_BDCR_LSEON;
    // Wait until LSE is stable
    while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0) ;

    // Flash setup for selected 80MHz@1.2V speed setting (4WS)
    FLASH->ACR = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_4WS;

    // MSI PLL (to LSE) activation
    RCC->CR |= RCC_CR_MSIPLLEN;

    // Update PLL
    // PLLM = 1 --> 000
    // PLLN = 40 --> 40
    // PPLLR = 2 --> 00
    // PLLDIV = unused, PLLP = unused (SAI3), PLLQ = unused (48M1)
    // SRC = MSI --> 01
    RCC->PLLCFGR = RCC_PLLCFGR_PLLREN | (40 << RCC_PLLCFGR_PLLN_Pos) | RCC_PLLCFGR_PLLSRC_MSI;

    // PLL activation
    RCC->CR |= RCC_CR_PLLON;

    /* Waiting for PLL lock.*/
    while ((RCC->CR & RCC_CR_PLLRDY) == 0) ;

    // RCC_CFGR is OK by defaut
    RCC->CFGR = 0;

    // CCIPR : no periph clock by default
    RCC->CCIPR = 0;

    // Switches on the PLL clock source
    RCC->CFGR = (RCC->CFGR  & ~RCC_CFGR_SW_Msk) | RCC_CFGR_SW_PLL;
    // Wait until SYSCLK is stable.
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) ;

    // Enable SYSCFG clock enabled
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

}