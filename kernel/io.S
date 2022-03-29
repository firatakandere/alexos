.globl outportb
outportb:
  movb 8(%esp), %al
  movw 4(%esp), %dx
  outb %al, %dx
  ret
