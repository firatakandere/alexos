/* consts */
.set STACK_SIZE, 0x4000 /* 16KiB stack */
.set GRUB_MULTIBOOT_ARCHITECTURE_I386, 0
.set MULTIBOOT2_HEADER_MAGIC, 0xe85250d6
.set MULTIBOOT2_HEADER_TAG_END, 0

  .text
  .globl start, _start

start:
_start:
  jmp multiboot_entry

  /* align 64 bits */
  .align 8

multiboot_header:
  .long MULTIBOOT2_HEADER_MAGIC
  .long GRUB_MULTIBOOT_ARCHITECTURE_I386
  .long multiboot_header_end - multiboot_header
  .long -(MULTIBOOT2_HEADER_MAGIC + GRUB_MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))

  /* required end tags */
  .short MULTIBOOT2_HEADER_TAG_END
  .short 0
  .long 8
multiboot_header_end:
multiboot_entry:
  /* init stack pointer */
  movl  $(stack + STACK_SIZE), %esp

  /* reset EFLAGS */
  pushl $0
  popf

  /* push pointer to mb info struct */
  //pushl %ebx
  /* push magic value */
  //pushl %eax

  /* Call main */
  call  cmain

  /* Halt */
  pushl $halt_message
  call  terminal_write

loop: hlt
  jmp loop

halt_message:
  .asciz  "Halted."

  /* stack area */
  .comm stack, STACK_SIZE
