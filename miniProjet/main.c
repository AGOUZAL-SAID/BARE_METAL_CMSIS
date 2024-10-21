#include "led.h"
#include "clocks.h"



int main(){
    led_init();
    clocks_init();
    while (1)
    {
    
        led_g_on();
        sleep(100);
        led_g_off();   
        sleep(100);
        led(LED_YELLOW);
        sleep(100);
        led(LED_BLUE);
        sleep(100);
        led(LED_OFF);
        sleep(100);
    }     
} 