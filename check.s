# General cases for ANDI
addi ra,zero,0x155
andi sp,ra,0x1b9

# Edge cases for ANDI


# General Cases for addi


# Edge Cases for ADDI



# END MY TESTS


# lui ra,0x65432
# addi ra,ra,291 # 0x65432123
# addi s1,s1,-400
# addi sp,ra,0
# addi gp,zero,1

# addi t0, t0, 2047   # max positive 12-bit
# addi t1, t1, -2048  # max negative 12-bit
# addi t2, zero, -1   # negative immediate
# addi t3, t2, 1      # from -1 to 0
# addi s2, zero, 2047 # max positive 12-bit

# sub gp,gp,sp
# lui s2,0xdeadc

