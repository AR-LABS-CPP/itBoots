#!/bin/bash

mkdir -p output

echo "Assembling ASM files..."
ASM_FILES=$(find src -name "*.asm")
ASM_OBJECTS=""

for file in $ASM_FILES; do
    filename=$(basename "$file" .asm)
    output_file="output/asm_${filename}.o"
    echo "  Assembling $file..."
    nasm -f elf32 "$file" -o "$output_file"
    if [ $? -ne 0 ]; then
        echo "Error: Assembly of $file failed"
        exit 1
    fi
    ASM_OBJECTS="$ASM_OBJECTS $output_file"
done

echo "Compiling C files..."
C_FILES=$(find src -name "*.c")
C_OBJECTS=""

for file in $C_FILES; do
    filename=$(basename "$file" .c)
    output_file="output/c_${filename}.o"
    echo "  Compiling $file..."
    gcc -m32 -fno-stack-protector -fno-pic -fno-pie -nostdlib -nostartfiles -nodefaultlibs -c "$file" -o "$output_file"
    if [ $? -ne 0 ]; then
        echo "Error: Compilation of $file failed"
        exit 1
    fi
    C_OBJECTS="$C_OBJECTS $output_file"
done

echo "Linking..."
ld -m elf_i386 -T src/linker/kernel.ld -o output/kernel $ASM_OBJECTS $C_OBJECTS
if [ $? -ne 0 ]; then
    echo "Error: Linking failed"
    exit 1
fi

echo "Copying Kernel File..."
mv output/kernel iso/boot/kernel
if [ $? -ne 0 ]; then
    echo "Error: Couldn't copy kernel file to boot dir"
    exit 1
fi

echo "Creating ISO..."
grub-mkrescue -o output/kernel.iso iso/
if [ $? -ne 0 ]; then
    echo "Error: ISO creation failed"
    exit 1
fi

echo "Build successful! ISO created at output/kernel.iso"

echo "Running in QEMU..."
qemu-system-i386 -cdrom output/kernel.iso \
    -serial stdio \
    -no-reboot \
    -no-shutdown \
    -d cpu_reset,int,guest_errors \