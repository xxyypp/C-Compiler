 make clean
 make bin/generate_mips
 bin/generate_mips test/programs/if_true/in.code.txt my_executable
 ./my_executable
 echo $?
