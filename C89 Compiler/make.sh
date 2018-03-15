make clean
make bin/c_compiler
rm tmp.elf
rm
echo "-----------------------------------"
cat tmp.c
echo "-----------------------------------"
cat tmp.c | bin/c_compiler
cat tmp.c | bin/c_compiler > tmp.s
echo "-----------------------------------"
echo "finished compile"
echo "Start to convert to .s"
mips-linux-gnu-gcc -static tmp.s -o tmp.elf
echo "-----------------------------------"
echo "finished elf -> start to make qemu "
qemu-mips tmp.elf
echo $?
echo "finished qemu"


