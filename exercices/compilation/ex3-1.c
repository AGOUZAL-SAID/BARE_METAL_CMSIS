#include <stdio.h> 
int data = 255;
int bss ;
int bss2 = 0 ;
const int  rodata = 5;


int main(){
    void *p = main;
    printf("adresse de section data    : %p \n ",&data);
    printf("adresse de section bss     :%p %p \n ",&bss , &bss2);
    printf("adresse de section rodata  :%p \n  ",&rodata);
    printf("adresse de section text    :%p \n ", p);
}

