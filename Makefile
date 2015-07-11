C_HEADERS_DIR = include
C_SOURCES_DIR = src
C_SOURCES = $(wildcard $(C_SOURCES_DIR)/*.c)
HEADERS = $(wildcard *.h)

IMAGE_DIR = build
IMAGE = $(IMAGE_DIR)/sparta.img

KERNEL_DIR = src
KERNEL = $(KERNEL_DIR)/kernel.bin

KERNEL_ENTRY = src/kernelentry.o
KERNEL_ENTRY_SOURCES = src

BOOTLOADER_DIR = build
BOOTLOADER = $(BOOTLOADER_DIR)/bootloader.bin
BOOTLOADER_SOURCES = src/bootloader

CC = gcc
CCFLAGS = -m32 -g -O0 -nostdlib -nostdinc -ffreestanding -w
INCLUDE = -I $(C_HEADERS_DIR)

LD = ld
LDFLAGS = -m elf_i386 -e main -T link.ld

run: kernel
	qemu-system-i386 -cpu core2duo -kernel $(KERNEL) -monitor stdio

debug_info: enable_debug_info kernel
	qemu-system-i386 -cpu core2duo -kernel $(KERNEL) -monitor stdio

debug: kernel 
	qemu-system-i386 -s -S -kernel $(KERNEL) -monitor stdio

enable_debug_info:
	$(eval CCFLAGS = $(CCFLAGS) -DDEBUG)

image: bootloader kernel
	cat $(BOOTLOADER) $(KERNEL) > $(IMAGE)

kernel: bootloader kernelentry objects
	$(LD) $(LDFLAGS) -o $(KERNEL) $(KERNEL_ENTRY) src/boot.o src/kernel.o $(filter-out %kernel.o, $(C_SOURCES:.c=.o))

objects:
	@for file in $(C_SOURCES); do \
		$(CC) $(CCFLAGS) $(INCLUDE) -c $$file -o `echo $$file | sed 's/\.c/\.o/'`; \
	done; \

kernelentry:
	nasm $(KERNEL_ENTRY_SOURCES)/entry.S -f elf32 -o $(KERNEL_ENTRY) -g

bootloader:
	nasm $(BOOTLOADER_SOURCES)/boot.s -felf -o src/boot.o -g

clean:	
	rm -fr $(C_SOURCES_DIR)/*.o
	rm -fr $(KERNEL)
	rm -fr $(BOOTLOADER)
	rm -fr $(IMAGE)
	
test:
	@echo "In future!"
