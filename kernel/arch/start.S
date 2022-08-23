.globl gdt_flush
.extern gp
gdt_flush:
  lgdt (gp)
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movw %ax, %ss
  jmp $0x08, $flush2
flush2:
  ret

.globl idt_load
.extern idtp
idt_load:
  lidt (idtp)
  ret

.macro macro_isr_gen n errcode
  .globl isr\n
isr\n:
  cli
  .ifeq \errcode
  pushl $0
  .endif
  pushl $\n
  jmp isr_common_stub
.endm

macro_isr_gen 0 0
macro_isr_gen 1 0
macro_isr_gen 2 0
macro_isr_gen 3 0
macro_isr_gen 4 0
macro_isr_gen 5 0
macro_isr_gen 6 0
macro_isr_gen 7 0
macro_isr_gen 8 1
macro_isr_gen 9 0
macro_isr_gen 10 1
macro_isr_gen 11 1
macro_isr_gen 12 1
macro_isr_gen 13 1
macro_isr_gen 14 1
macro_isr_gen 15 0
macro_isr_gen 16 0
macro_isr_gen 17 0
macro_isr_gen 18 0
macro_isr_gen 19 0
macro_isr_gen 20 0
macro_isr_gen 21 0
macro_isr_gen 22 0
macro_isr_gen 23 0
macro_isr_gen 24 0
macro_isr_gen 25 0
macro_isr_gen 26 0
macro_isr_gen 27 0
macro_isr_gen 28 0
macro_isr_gen 29 0
macro_isr_gen 30 0
macro_isr_gen 31 0


; .extern fault_handler

isr_common_stub:
  pusha
  push %ds
  push %es
  push %fs
  push %gs
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movl %esp, %eax
  pushl %eax
  movl $fault_handler, %eax
  call *%eax
  popl %eax
  popl %gs
  popl %fs
  popl %es
  popl %ds
  popa
  addl $8, %esp
  iret


.macro macro_irq_gen n
.globl irq\n
irq\n:
  cli
  pushl $0
  pushl $(\n+32)
  jmp irq_common_stub
.endm

macro_irq_gen 0
macro_irq_gen 1
macro_irq_gen 2
macro_irq_gen 3
macro_irq_gen 4
macro_irq_gen 5
macro_irq_gen 6
macro_irq_gen 7
macro_irq_gen 8
macro_irq_gen 9
macro_irq_gen 10
macro_irq_gen 11
macro_irq_gen 12
macro_irq_gen 13
macro_irq_gen 14
macro_irq_gen 15

.extern irq_handler

irq_common_stub:
  pusha
  push %ds
  push %es
  push %fs
  push %gs
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movl %esp, %eax
  pushl %eax
  movl $irq_handler, %eax
  call *%eax
  popl %eax
  pop %gs
  pop %fs
  pop %es
  pop %ds
  popa
  addl $8, %esp
  iret
