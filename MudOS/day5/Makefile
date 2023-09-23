IMAGE = mudos.img

C_FLAGS := -Wall -g -m32 -fno-pie
CFLAGS += -ffunction-sections -nostdlib -nostdinc -fno-builtin -ffreestanding -fno-stack-protector -fno-asynchronous-unwind-tables
QEMU_FLAGS := -fda mudos.img

ifdef NONO
QEMU_FLAGS += -daemonize
endif

ifdef DEBUG
QEMU_FLAGS += -s -S
endif

all: ipl.o mud.o func.o bootpack.o
	ld -m elf_i386 -T mud.ld -Map=final.map -o mud.bin $^
	objdump -D -b binary -m i8086 -Maddr16,data16 mud.bin > mud.lst
	dd if=/dev/zero of=$(IMAGE) bs=512 count=2880
	dd if=mud.bin of=$(IMAGE) bs=512 conv=notrunc

%.o: %.s
	as -g --32 -o $@ $<

bootpack.o: bootpack.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf *.bin *.img *.lst *.elf *.o *.html *.map

qemu: all
	qemu-system-i386 $(QEMU_FLAGS)

.PHONY:
	all
