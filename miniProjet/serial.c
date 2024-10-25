#include "uart.h"
#include"clocks.h"
uint32_t volatile sum ; 

int main() {
    uart_init(); // Initialize UART
    clocks_init(); 
    sum = uart_calculate(1000);
    return sum;

}
