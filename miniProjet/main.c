#include "clocks.h"
#include "irq.h" 
#include "matrix.h"
#include <stdint.h>
#include "uart.h"
#include "buttons.h"
#include "led.h"
#include "uart_irq.h"
#include "timer.h"

int main(){

    clocks_init();
    led_init();
    uart_init(38400);
    matrix_init();
    irq_init();
    button_init();
    init_tram();
    enable_interruption_uart();
    timer_init(1000000/480);
} 
