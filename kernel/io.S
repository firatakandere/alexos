.globl outportb
outportb:
  movb 8(%esp), %al
  movw 4(%esp), %dx
  outb %al, %dx
  ret

.globl inportb

inportb:
  movw 4(%esp), %dx
  inb %dx, %al
  ret

