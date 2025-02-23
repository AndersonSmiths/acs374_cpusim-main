#include "sol.h"
#include <stdio.h>

/// TODO
uint32_t fetch(uint64_t PC, uint32_t *instructions)
{
    return instructions[PC / 4];
}

// TODO
info decode(uint32_t instruction)
{
    info decoded;

    // selecting all components of type I
    uint32_t rs1 = (instruction >> 15) & 0x1F; 
    uint32_t imm12 = (instruction >> 20) & 0xFFF;
    uint32_t opcode = instruction & 0x7F;         
    uint32_t rd = (instruction >> 7) & 0x1F;  
    uint32_t funct3 = (instruction >> 12) & 0x7; 

    // 
    if (opcode == 0x13) {
        switch (funct3) {
            // ADDI
            case 0x0:
                decoded.inst = ADDI;
                break;
            // ORI
            case 0x6: 
                decoded.inst = ORI;
                break;
            // AND
            case 0x7:
                decoded.inst = ANDI;
                break;
            // XORI
            case 0x4: 
                decoded.inst = XORI;
                break;
            // invalid funct3 edge case
            default:
                decoded.inst = 0;
                break;
        }

        decoded.first = registers[rs1];
        decoded.second = 
        decoded.third = rd;
    } else {
        decoded.inst = 0;
        decoded.first = 0;
        decoded.second = 0;
        decoded.third = 0;
    }

    // sign extension for immediate
    int32_t extended;
    if (imm12 & 0x800) {
        extended = (int32_t)(imm12 | 0xFFFFF000);
    } else {
        extended = (int32_t)imm12;
    }

    return decoded;
    
}

// TODO
info execute(info information)
{
}

// TODO
info memory(info information)
{
}

// TODO
uint64_t writeback(uint64_t PC, info information)
{
}
