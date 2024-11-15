MEMORY
{
rom (rx)   : ORIGIN = 0x08000000, LENGTH = 1M
sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}


_stack = ORIGIN(sram2) + LENGTH(sram2) ;

LMA_vector  = LOADADDR(.vector_table)     ;
LMA_text    = LOADADDR(.text)             ;
LMA_data    = LOADADDR(.data)             ;
LMA_bss     = LOADADDR(.bss)              ;


LENGTH_vector  = SIZEOF(.vector_table)  ;
LENGTH_text    = SIZEOF(.text)          ;
LENGTH_data    = SIZEOF(.data)          ;
LENGTH_bss     = SIZEOF(.bss)           ;


SECTIONS {

    .vector_table : {
        VMA_vector = .;
        *(.vector_table)
    } >sram1 AT>rom
    
    .copage_section : {
        *(.copage_section)
    }>rom
    
    .text : {
        VMA_text = . ;
        *(.text)
    }>sram1 AT>rom


    .rodata : {
        *(.rodata)
    }>rom 


    .data : {
        VMA_data = . ; 
        *(.data)
    }>sram1 AT>rom


    .bss : {
        _bstart = . ;
        *(.bss)
        _bend = .;
    }>sram1 AT>rom

}

ENTRY(_start)
