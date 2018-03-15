make clean
make bin/c_compiler
cat tmp.c | bin/c_compiler > tmp.s
mips-linux-gnu-gcc -static tmp.s -o tmp.elf
qemu-mips tmp.elf
