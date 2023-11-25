.code16
.global mudstart

.equ BOTPAK, 0x00280000
.equ DSKCAC, 0x00100000
.equ DSKCAC0, 0x00008000


.equ CYLS, 0xf0
.equ LEDS, 0x0ff1
.equ VMODE, 0x0ff2
.equ SCRNX, 0x0ff4
.equ SCRNY, 0x0ff6
.equ VRAM, 0x0ff8

mudstart:
    mov $0x13, %al
    mov $0x00, %ah
    int $0x10
    movb $8, (VMODE)
    movw $320, (SCRNX)
    movw $200, (SCRNY)
    movl $0x000a0000, (VRAM)

    mov $0x02, %ah
    int $0x16
    mov %al, (LEDS)

    mov $0xff, %al
    out %al, $0x21
    nop
    out %al, $0xa1
    cli

    call waitkbdout
    mov $0xd1, %al
    out %al, $0x64
    call waitkbdout
    mov $0xdf, %al
    out %al, $0x60
    call waitkbdout

    lgdt (GDTR0)
    mov %cr0, %eax
    and $0x7fffffff, %eax
    or $0x00000001, %eax
    mov %eax, %cr0
    jmp pipelineflush

pipelineflush:
    mov $8, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    mov $bootpack, %esi
    mov $BOTPAK, %edi
    mov $512*1024/4, %ecx
    call memcpy

    mov $0x7c00, %esi
    mov $DSKCAC, %edi
    mov $512/4, %ecx
    call memcpy

    mov $DSKCAC0+512, %esi
    mov $DSKCAC+512, %edi
    mov $0, %ecx
    mov (CYLS), %cl
    imul $512*18*2/4, %ecx
    sub $512/4, %ecx
    call memcpy

skip:
    mov $0xffff, %esp
    ljmpl $0x10, $0x0000

waitkbdout:
    in $0x64, %al
    and $0x02, %al
    jnz waitkbdout
    ret

memcpy:
    mov (%esi), %eax
    add $4, %esi
    mov %eax, (%edi)
    add $4, %edi
    sub $1, %ecx
    jnz memcpy
    ret

.align 16
GDT0:
    .space 8, 0
    .word 0xffff, 0x0000, 0x9200, 0x00cf
    .word 0xffff, 0x0000, 0x9a28, 0x0047
    .word 0

GDTR0:
    .word 8*3-1
    .long GDT0
.align 16


bootpack:
