.code16
.global init
.equ CYLD, 10

init:
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

// read the hard drive, 0,0,2
    mov $0x0820, %ax
    mov %ax, %es
    mov $0, %ch #cylinder 0
    mov $0, %dh #head 0
    mov $2, %cl #sector 2

readloop:
    mov $0, %si #record fail times

retry:
    mov $2, %ah
    mov $1, %al #read 1 sector
    mov $0, %bx #shift in segment
    mov $0, %dl #driver no.
    int $0x13
    jnc next

    add $1, %si
    cmp $5, %si
    jae error
    mov $0, %ah
    mov $0, %dl
    int $0x13
    jmp retry

next:
    // increse segment addr, 0x20 = 512B/16
    mov %es, %ax
    add $0x20, %ax
    mov %ax, %es

    add $1, %cl
    cmp $18, %cl
    jbe readloop
    mov $1, %cl
    add $1, %dh
    cmp $2, %dh
    jb readloop
    mov $0, %dh
    add $1, %ch
    cmp $CYLD, %ch
    jb readloop

    // go to 0xc200, which is 0x8000+0x4200, 0x4200 is where our program begin from disk
    jmp mudstart

fin:
    hlt
    jmp fin

error:
    mov msg, %si

putloop:
    mov (%si), %al
    add $1, %si
    cmp $0, %al

    je fin
    mov $0x0e, %ah
    mov $15, %bx
    int $10
    jmp putloop

msg:
    .byte 0x0a, 0x0a
    .ascii "load error"
    .byte 0x0a
    .byte 0

    .org 0x1fe
    .byte 0x55, 0xaa
