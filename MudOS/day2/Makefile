all:
	as -g --32 -o helloos.o helloos.S
	ld -m elf_i386 --oformat binary -Ttext 0x7c00 -o helloos.bin helloos.o
	objdump -D -b binary -mi386 -Maddr16,data16 helloos.bin > helloos.lst
	dd if=/dev/zero of=helloos.img bs=512 count=2880
	dd if=helloos.bin of=helloos.img bs=512 count=1 conv=notrunc

clean:
	rm -rf *.bin *.img *.lst *.elf *.o

qemu: all
	qemu-system-i386 -fda helloos.img -s -S

.PHONY:
	all
