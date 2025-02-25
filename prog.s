# TYPE I General Cases for ADDI
#addi ra,zero,0x155
#addi t0,zero,0x13ddf4

#  TYPE I Edge Cases for ADDI
#addi t1,zero,-2048
#addi t2,zero,2047
#addi t3,t1,1

# TYPE I General Cases for ANDI
#andi sp,ra,0x1b9

# TYPE I Edge Cases for ANDI
#addi t1,zero,0xfff
#andi t1,t1,-2048
#addi t2,zero,0xfff
#andi t2,t2,2047
#addi t3,zero,0xabcd
#andi t3,t3,-1

# TYPE I Edge Cases for ORI
#addi t1,zero,-1
#ori t1,t1,-2048
#addi t2,zero,-1
#ori t2,t2,2047
#addi t3,zero,0x6b3
#ori t3,t3,-1


# TYPE I Edge Cases for XORI
addi t1,zero,-1
xori t1,t1,-2048
addi t2,zero,-1
xori t2,t2,2047
addi t3,zero,0x6b3
xori t3,t3,-1


# TYPE R General Cases
#addi t0,zero,10
#addi t1,zero,4
#add t2,t0,t1
#sub t3,t0,t1
#and t4,t0,t1
#sll t5,t0,t1
#sra t6,t5,t1

# TYPE R - Edge Cases
#addi t3,zero,-1   
#add t4,t3,1       
#sub t5,zero,t3    

# TYPE U General Cases
# lui ra,0x65432

# TYPE U Edge Cases
# lui ra,0x00000    
# lui ra,0xFFFFF     


# TYPE B
#addi t0,zero,5
#addi t1,zero,10
#beq t0,t1,branch
#addi s0,zero,0
#branch:
#addi s0,zero,0x249

# TYPE B Edge Cases

# Branch Taken
#addi t0,zero,0x1d
#addi t1,zero,0x1d
#beq t0,t1,branchEdge
#addi s0,zero,0x3b7
#branchEdge:
#addi s0,zero,0x7d2


# Branch Free
#addi t0,zero,5
#addi t1,zero,6
#beq t0,t1,branchThree
#addi s0,zero,0x1f3
#branchThree:
#addi s0,zero,0x2ac

# TYPE S
# addi t0,zero,0x7ab
# addi t1,zero,4
# sw t0,0(t1)
# lw t2,0(t1)


# TYPE S - Edge Cases
# addi t0,zero,0x7ab    
# addi t1,zero,-4       
# sw t0,0x7ff(t1)       
# lw t2,0x7ff(t1)      


