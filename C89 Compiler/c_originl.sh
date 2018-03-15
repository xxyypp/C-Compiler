cat tmp.c
echo "-----------------------------------"
echo "-----------------------------------"
echo "finished compile"
echo "Start to convert to .s"
mips-linux-gnu-gcc -c -S -x c  tmp.c -o tmp.s
cat tmp.s
echo "-----------------------------------"
mips-linux-gnu-gcc -static tmp.s -o tmp.elf
echo "-----------------------------------"
echo "finished elf -> start to make qemu "
qemu-mips tmp.elf
echo $?
echo "finished qemu"


