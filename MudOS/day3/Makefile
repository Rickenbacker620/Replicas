IMAGE = mudos.img

QEMU_FLAGS = -daemonize -fda mudos.img

ifdef NONO
QEMU_FLAGS += -daemonize
endif

ifdef DEBUG
QEMU_FLAGS += -s -S
endif

all: ipl.o mud.o
	ld -m elf_i386 -T mud.ld -Map=final.map -o mud.bin $^
	objdump -D -b binary -m i8086 -Maddr16,data16 mud.bin > mud.lst
	dd if=/dev/zero of=$(IMAGE) bs=512 count=2880
	dd if=mud.bin of=$(IMAGE) bs=512 conv=notrunc

%.o: %.s
	as -g --32 -o $@ $<

clean:
	rm -rf *.bin *.img *.lst *.elf *.o *.html *.map

qemu: all
	qemu-system-i386 $(QEMU_FLAGS)

.PHONY:
	all
