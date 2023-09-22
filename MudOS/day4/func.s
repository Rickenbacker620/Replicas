.code32
.global io_hlt
.global write_mem8

io_hlt:
    hlt
    ret

write_mem8:
    mov 4(%esp), %ecx
    mov 8(%esp), %al
    mov %al, (%ecx)
    ret
