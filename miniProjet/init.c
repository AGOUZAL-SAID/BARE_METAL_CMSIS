#include <stdint.h>
extern uint8_t _bstart ;
extern uint8_t _bend;
void init_bss(){
    uint8_t * p = (uint8_t * ) &_bstart;
    uint8_t * finish = (uint8_t * ) &_bend; 
    while (p <= finish){
        *p =0;
        p++;
    }  
} 
