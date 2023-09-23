.code32

.global io_hlt, io_cli, io_sti, io_stihlt
.global io_in8, io_in16, io_in32
.global io_out8, io_out16, io_out32
.global io_load_eflags, io_store_eflags
.global io_load_cr0, io_store_cr0

io_hlt:
    hlt
    ret

io_cli:
    cli
    ret

io_sti:
    sti
    ret

io_stihlt:
    sti
    hlt
    ret

io_in8:
    mov 4(%esp), %edx
    mov 0, %eax
    in %dx, %al
    ret

io_in16:
    mov 4(%esp), %edx
    mov 0, %eax
    in %dx, %ax
    ret

io_in32:
    mov 4(%esp), %edx
    in %dx, %eax
    ret

io_out8:
    mov 4(%esp), %edx
    mov 8(%esp), %al
    out %al, %dx
    ret

io_out16:
    mov 4(%esp), %edx
    mov 8(%esp), %ax
    out %ax, %dx
    ret

io_out32:
    mov 4(%esp), %edx
    mov 8(%esp), %eax
    out %eax, %dx
    ret

io_load_eflags:
    pushfl
    pop %eax
    ret

io_store_eflags:
    mov 4(%esp), %eax
    push %eax
    popfl
    ret

io_load_cr0:
    mov %cr0, %eax
    ret

io_store_cr0:
    mov 4(%esp), %eax
    mov %eax, %cr0
    ret