#include "memfuncs.h"

extern uint8_t * LMA_vector        ;
extern uint8_t * LMA_text          ;
extern uint8_t * LMA_rodata        ;
extern uint8_t * LMA_data          ;
extern uint8_t * LMA_bss           ;

extern uint8_t VMA_vector          ;
extern uint8_t VMA_text            ;
extern uint8_t VMA_rodata          ;
extern uint8_t VMA_data            ;
extern uint8_t _bstart             ;

extern int LENGTH_vector           ;           
extern int LENGTH_text             ;
extern int LENGTH_rodata           ;
extern int LENGTH_data             ;
extern int LENGTH_bss              ;


void copy_sections(){
    memcpy(&VMA_text,LMA_text,LENGTH_text);
    memcpy(&_bstart,LMA_bss,LENGTH_bss);
    memcpy(&VMA_data,LMA_data,LENGTH_data);
    memcpy(&VMA_vector,LMA_vector,LENGTH_vector);
    }








