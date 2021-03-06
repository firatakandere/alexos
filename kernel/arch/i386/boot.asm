; Multiboot header constants

MBALIGN  equ     1 << 0
MEMINFO  equ     1 << 1
FLAGS    equ     MBALIGN | MEMINFO
MAGIC    equ     0x1BADB002
CHECKSUM equ     -(MAGIC + FLAGS)

; Write multiboot headers
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Provide stack
KERNEL_STACK_SIZE equ 16384 ; 16 KiB

section .bss
align 16
stack_bottom:
    resb KERNEL_STACK_SIZE
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top

    push eax ; magic number 
    push ebx ; multiboot info
    extern kernel_main
    call kernel_main

    cli
.hang hlt
    jmp .hang
.end:
