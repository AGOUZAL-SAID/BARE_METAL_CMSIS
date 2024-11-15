#include "memfuncs.h"

extern uint8_t  LMA_vector        ;
extern uint8_t  LMA_text          ;
extern uint8_t  LMA_rodata        ;
extern uint8_t  LMA_data          ;
extern uint8_t  LMA_bss           ;

extern uint8_t VMA_vector          ;
extern uint8_t VMA_text            ;
extern uint8_t VMA_rodata          ;
extern uint8_t VMA_data            ;
extern uint8_t _bstart             ;

extern uint32_t LENGTH_vector           ;           
extern uint32_t LENGTH_text             ;
extern uint32_t LENGTH_rodata           ;
extern uint32_t LENGTH_data             ;
extern uint32_t LENGTH_bss              ;


__attribute__((section(".copage_section")))void copy_sections(){
    memcpy(&VMA_text,&LMA_text,(uint32_t)&LENGTH_text);
    memcpy(&_bstart,&LMA_bss,(uint32_t)&LENGTH_bss);
    memcpy(&VMA_data,&LMA_data,(uint32_t)&LENGTH_data);
    memcpy(&VMA_vector,&LMA_vector,(uint32_t)&LENGTH_vector);
    }








