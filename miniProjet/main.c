#include "led.h"
int main(){
    led_init();
    //for (int i =0 ; i<10 ; i++){
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