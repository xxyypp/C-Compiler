.globl main
.ent main
main:
addiu	$sp,$sp,-80
sw	$fp,4($sp)
move	$fp,$sp
sw $0 , 4($sp)
addiu $t1,$0,10
sw $t1, 4($sp)
lw $2, 4($sp)
move $sp,$fp
lw	$fp,4($sp)
addiu	$sp,$sp,80
j $31
nop

