ENTRY(init)
OUTPUT_ARCH(i386)
OUTPUT_FORMAT("binary")

SECTIONS {

    .ipl 0x7c00: AT(0x0000){
        ipl.o(.text)
    }

    .mud 0xc200: AT(0x4200){
        mud.o(.text)
        bootpack.o(.text)
        func.o(.text)
    }
}
