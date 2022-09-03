.globl set_page_directory
set_page_directory:
    movl 4(%esp),%eax
    movl %eax, %cr3
    ret

.globl enable_paging
enable_paging:
    movl %cr0, %eax
    orl $0x80000000, %eax
    movl %eax, %cr0
    ret