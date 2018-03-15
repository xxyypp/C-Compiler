echo "-----------------------------------"
echo "-----------------------------------"
echo "finished compile"
echo "Start to convert to .s"
cat tmp.s
echo "-----------------------------------"
mips-linux-gnu-gcc -static tmp.s -o tmp.elf
echo "-----------------------------------"
echo "finished elf -> start to make qemu "
qemu-mips tmp.elf
echo $?
echo "finished qemu"


