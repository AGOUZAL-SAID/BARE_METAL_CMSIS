#include "uart.h"
#include"clocks.h"
uint32_t volatile sum ; 

int main() {
    uart_init(); // Initialize UART
    clocks_init();
    //uint32_t n =  10000; 
    sum = uart_calculate(1000);
    return sum;

}
