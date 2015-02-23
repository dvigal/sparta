C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ = ${C_SOURCES:.c=.o}
all: kernel.img

run: all
	bochs
kernel.img: bootloader.bin kernel.bin
	cat $^ > kernel.img

kernel.bin: entry.o kernel.o ${OBJ}
	ld -m elf_i386 -e main -M -Ttext 0x1000 -o kernel.bin $^ --oformat binary

%.o: %.c ${_HEADERS_}
	gcc -m32 -g -O0 -nostdlib -nostdinc -ffreestanding -c $< -o $@

entry.o: entry.S
	nasm $< -f elf32 -o $@

bootloader.bin: bootloader.S
	nasm $< -f bin -o $@

clean:
	rm -fr *.bin *.dis *.o kernel.img
	rm -fr *. o *.bin 
