# General cases for ADDI
# addi ra,zero,0x155  expected: 0x155 at register 1 (works)
# addi t0,zero,0x123   expected: 0x123 at register t0 register 5 ()

# Edge cases for ADDI
# addi t1,zero,-2048  expected: 0xFFFFFFFFFFFFF800 at t1 register 6 (works)
# addi t2,zero,2047  expected: 0x7FF at register t2 register 7 (works)
# addi t3,t1,1  expected: 0xFFFFFFFFFFFFF801 at t3 register 28 (works)

# General Cases for ANDI
# andi sp,ra,0x1b9 # expected: 0x11 at register 2


# Edge cases for ANDI
addi t1,zero,0xFFFF   # expected: 0xFFFF at register t1 register 6
andi t1,t1,-2048      # expected: 0xF800 at register t1 register 6
addi t2,zero,0xFFFF   # expected: 0xFFFF at register t2 register 7
andi t2,t2,2047       # expected: 0x7FF at register t2 register 7
addi t3,zero,0xABCD   # expected: 0xABCD at register t3 register 28
andi t3,t3,-1        # expected: 0xABCD at register t3 register 28





# General Cases for addi


# Edge Cases for ADDI



# lui ra,0x65432
# addi ra,ra,291 # 0x65432123
# addi s1,s1,-400
# addi sp,ra,0
# addi gp,zero,1
# sub gp,gp,sp
# lui s2,0xdeadc
