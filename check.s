# TYPE I - General Cases for ADDI
#addi ra,zero,0x155
#addi t0,zero,0x13ddf4
#
#  TYPE I - Edge Cases for ADDI
#addi t1,zero,-2048
#addi t2,zero,2047
#addi t3,t1,1
#
# TYPE I - General Cases for ANDI
#andi sp,ra,0x1b9
#
# TYPE I - Edge Cases for ANDI
#addi t1,zero,0xfff
#andi t1,t1,-2048
#addi t2,zero,0xfff
#andi t2,t2,2047
#addi t3,zero,0xabcd
#andi t3,t3,-1
#
# TYPE R - General Cases
addi t0,zero,10
addi t1,zero,4
add t2,t0,t1
sub t3,t0,t1
and t4,t0,t1
sll t5,t0,t1
sra t6,t5,t1

# TYPE R - Edge Cases
#addi t7,zero,-1
#add t8,t7,1
#sub t9,zero,t7
#
# TYPE U
#lui ra,zero,0x65432
#
# TYPE B
#addi t0,zero,1
#addi t1,zero,1
#beq t0,t1,branch
#addi s0,zero,0
#branch:
#addi s0,zero,0x123
#
# TYPE S
#addi t0,zero,0xabcd
#addi t1,zero,4
#sw t0,t1,0
#lw t2,t1,0
#
# General Cases for addi
#
# Edge Cases for ADDI
#
# ORIGINAL 
# lui ra,0x65432
# addi ra,ra,291
# addi s1,s1,-400
# addi sp,ra,0
# addi gp,zero,1
# sub gp,gp,sp
# lui s2,0xdeadc
