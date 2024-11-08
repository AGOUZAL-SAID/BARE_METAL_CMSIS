#include "clocks.h"
#include "irq.h" 
#include "matrix.h"
#include <stdint.h>
#include "uart.h"
#include "uart_irq.h"
#include "timer.h"

int main(){
    clocks_init();
    uart_init(38400);
    matrix_init();
    irq_init();
    init_tram();
    enable_interruption_uart();
    timer_init(1000);
} 
