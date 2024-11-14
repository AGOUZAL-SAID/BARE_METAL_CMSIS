MEMORY
{
rom (rx)   : ORIGIN = 0x08000000, LENGTH = 1M
sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}


_stack = ORIGIN(sram2) + LENGTH(sram2) ;

SECTIONS {

    .vector_table : AT(ORIGIN(rom)) {
        *(.vector_table)
    } >rom

    .text : {
        *(.text)
    }>rom


    .rodata : {
        *(.rodata)
    }>rom 


    .data : {
        *(.data)
    }>sram1


    .bss : {
        _bstart = . ;
        *(.bss)
        _bend = .;
    }>sram1

}

ENTRY(_start)
