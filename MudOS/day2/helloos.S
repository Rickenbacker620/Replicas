.code16
.global _start

_start:
    jmp entry
    nop
    .ascii "HELLOIPL"
    .word 512
    .byte 1
    .short 1
    .byte 2
    .short 224
    .short 2880
    .byte 0xf0
    .short 9
    .short 18
    .short 2
    .long 0
    .long 2880
    .byte 0
    .byte 0
    .byte 0x29
    .long 0xffffffff
    .ascii "HELLO-OS   "
    .ascii "FAT12   "
    .space 18, 0

entry:
    mov $0, %ax
    mov %ax, %ss
    mov $0x7c00, %sp
    mov %ax, %ds
    mov %ax, %es

    mov $msg, %si
putloop:
    mov (%si), %al
    add $1, %si
    cmp $0, %al

    je fin
    mov $0x0e, %ah
    mov $15, %bx
    int $0x10
    jmp putloop

fin:
    hlt
    jmp fin

msg:
    .byte 0x0a, 0x0a
    .ascii "hello, world"
    .byte 0x0a
    .byte 0

    .org 0x1fe
    .byte 0x55, 0xaa
