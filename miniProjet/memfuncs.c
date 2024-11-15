#include <stdint.h>
typedef unsigned int size_t ;


void * memset(void * bstart ,int a,size_t size){
    unsigned int finish =0;
    uint8_t * p = (uint8_t *) bstart;
    while (finish <= size){
        *p =(uint8_t) a ;
        p++;
    }
    return bstart ;
}


int memcmp( const void * mem1_p, const void * mem2_p, size_t size ){ 
    for( unsigned int position=0; position<size ; ++position ) {
        int cmp = *( uint8_t  * ) mem1_p++ - * (uint8_t  *) mem2_p++;
        if ( cmp ) return cmp;
    }
    return 0;
} 

__attribute__((section(".copage_section")))void * memcpy( void * destination, const void * source, size_t size ){ 
    for (unsigned int position=0; position<size; ++position ){
        *(uint8_t *)destination = * (uint8_t * )source ;
        destination++;
        source++; 
    }  
    return destination;
}  

void * memmove( void * destination, const void * source, size_t size ){ 
    uint8_t  intermedium = 0;
    for (unsigned int position=0; position<size; ++position ){
        if (destination !=source){
            *(uint8_t *)destination = * (uint8_t *)source ;
            destination++;
            source++; 
            } 
        else{
            intermedium = * (uint8_t *)source ; 
            *(uint8_t *)destination = intermedium;
            source++;
            destination++;
        }     
    }  

    return destination;
} 
