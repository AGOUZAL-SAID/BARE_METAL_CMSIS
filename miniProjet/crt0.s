.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start


_start:
ldr r13, =0x10007fff
bl init_bss
bl main
_exit: b _exit
