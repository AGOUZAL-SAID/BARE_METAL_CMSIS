#include "matrix.h"
#include "clocks.h"
#include "irq.h"
#include "buttons.h"
#include "led.h"

int main(){

    clocks_init();
    matrix_init();
    irq_init();
    led_init();
    button_init();                 
    test_static();
} 
