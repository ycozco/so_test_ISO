# Definir los directorios de código fuente
C_SOURCES = $(wildcard kernel/*/*.c) $(wildcard kernel/*/*/*.c)
ASM_SOURCES = $(wildcard kernel/*/*.asm) $(wildcard kernel/*/*/*.asm) $(wildcard kernel/scheduler/*.asm)

# Generar los objetos correspondientes
C_OBJECTS = ${C_SOURCES:.c=.o}
ASM_OBJECTS = ${ASM_SOURCES:.asm=.o}

.PHONY : all assemble run clean

all: run

run : assemble
    qemu-system-i386 -drive format=raw,file=disk.img -monitor stdio

debug: assemble
    qemu-system-i386 -s -hda disk.img &
    gdb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf" -ex "b kmain" -ex "continue"

assemble: disk.img kernel.bin stage1.bin stage2.bin
    dd if=stage1.bin of=disk.img bs=1 count=3 seek=0 skip=0 conv=notrunc
    dd if=stage1.bin of=disk.img bs=1 count=451 seek=62 skip=62 conv=notrunc
    mcopy -i disk.img stage2.bin kernel.bin :: -D o

kernel.bin : kernel/kernel.elf
    objcopy -O binary $^ $@
    chmod -x $@

# Puedes usar la opción --print-map para ver qué hace el enlazador
kernel/kernel.elf : $(C_OBJECTS) $(ASM_OBJECTS)
    i686-elf-ld $^ -T kernel/mem/linker.ld -o $@
    chmod -x $@

%.o : %.c
    i686-elf-gcc -Ikernel/include -Ikernel/scheduler -ffreestanding -c $< -o $@ -Wall -Werror -g

%.o : %.asm
    nasm $< -f elf32 -o $@

stage1.bin : boot/stage1/stage1.asm
    nasm $^ -f bin -o $@

stage2.bin : boot/stage2/stage2.asm
    nasm $^ -f bin -o $@

disk.img:
    truncate $@ -s 1M
    mkfs.vfat -F 12 -S 512 -s 1 $@

clean:
    rm -f $(C_OBJECTS) $(ASM_OBJECTS) kernel/kernel.elf kernel.bin stage1.bin stage2.bin