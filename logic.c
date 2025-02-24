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
    uint32_t rs2   = (instruction >> 20) & 0x1F;  
    uint32_t funct7 = (instruction >> 25) & 0x7F; 

    // sign extension for immediate
    int32_t extended;
    if (imm12 & 0x800) {
        extended = (int32_t)(imm12 | 0xFFFFF000);
    } else {
        extended = (int32_t)imm12;
    }


    // TYPE I
    // TYPE I
    // TYPE I
    // TYPE I
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
        decoded.second = extended;
        decoded.third = rd;
    // alternate type I opcode
    } else if (opcode == 0x03) {
        switch (funct3) {
            // LB
            case 0x0: 
                decoded.inst = LB;
                break;
            // LW
            case 0x2: 
                decoded.inst = LW;
                break;
            // LD
            case 0x3:
                decoded.inst = LD;
                break;
            default:
                decoded.inst = 0;
                break;
        }
        decoded.first = registers[rs1];    
        decoded.second = extended;         
        decoded.third = rd;  

    // TYPE R    
    // TYPE R    
    // TYPE R    
    // TYPE R    
    } else if (opcode == 0x33) {
        // 
        uint32_t destReg = (instruction >> 7) & 0x1F;
        switch (funct3) {
            case 0x0:
                if (funct7 == 0x20) {
                    // SUB
                    decoded.inst = SUB;
                } else {
                    // ADD
                    decoded.inst = ADD;
                }
                break;
            case 0x7:
                // AND
                decoded.inst = AND;
                break;
            case 0x2:
                // SLT
                decoded.inst = SLT;
                break;
            case 0x1:
                // SLL
                decoded.inst = SLL;
                break;
            case 0x5:
                if (funct7 == 0x20) {
                    // SRA
                    decoded.inst = SRA;
                }
                break;
            default:
                decoded.inst = 0;
                break;
        }
        decoded.first  = registers[rs1];
        decoded.second = registers[rs2];
        decoded.third  = destReg;
    }
    // TYPE U
    // TYPE U
    // TYPE U
    // TYPE U
    // TYPE U
    else if (opcode == 0x37) {
        decoded.inst = LUI;
        uint64_t upper = (uint64_t)(instruction & 0xFFFFF000);
        decoded.first = 0;       
        decoded.second = upper;  
        decoded.third = rd;      
    }

    // TYPE S
    // TYPE S
    // TYPE S
    // TYPE S
    else if (opcode == 0x23) {
        uint32_t lowerImmediate = (instruction >> 7) & 0x1F;
        uint32_t upperImmediate = (instruction >> 25) & 0x7F;
        int32_t storeOffset = (int32_t)((upperImmediate << 5) + lowerImmediate);
        if (storeOffset & 0x800) {
            storeOffset |= 0xFFFFF000;
        }
        switch (funct3) {
            // SB
            case 0x0: 
                decoded.inst = SB;
                break;
            // SW
            case 0x2:
                decoded.inst = SW;
                break;
            // SD
            case 0x3: 
                decoded.inst = SD;
                break;
            // edge case purposes
            default:
                decoded.inst = 0;
                break;
        }
        decoded.first = registers[rs1];   
        decoded.second = storeOffset;      
        decoded.third = registers[rs2];     
    }
    // TYPE B
    // TYPE B
    // TYPE B
    // TYPE B
    // TYPE B
    else if (opcode == 0x63) {
        uint32_t registerTwo = (instruction >> 20) & 0x1F;
        uint32_t registerOne = rs1;
        int32_t branchOffset = (((instruction >> 31) & 0x1) << 12) + (((instruction >> 25) & 0x3F) << 5) + (((instruction >> 8) & 0xF) << 1) + (((instruction >> 7) & 0x1) << 11);
        if (branchOffset & 0x1000) {
            branchOffset = branchOffset - 0x2000;
        }
        // only 1 case: BEQ, else 0 for edge case purposes
        switch (funct3) {
            case 0x0: 
                decoded.inst = BEQ;
                break;
            default:
                decoded.inst = 0;
                break;
        }
        decoded.first  = registers[registerOne];   
        decoded.second = registers[registerTwo]; 
        decoded.third  = (uint64_t)branchOffset;
    }
    return decoded;
    
}

// TODO
info execute(info information)
{
    switch (information.inst) {
        // ADDI
        case ADDI:
            information.first = information.first + information.second;
            break;
        // ORI
        case ORI:
            information.first = information.first | information.second;
            break;
        // ANDI
        case ANDI:
            information.first = information.first & information.second;
            break;
        // XORI
        case XORI:
            information.first = information.first ^ information.second;
            break;
        // LB, LW, LD => compute address
        case LB:
        case LW:
        case LD:
            information.first = information.first + (int64_t)information.second;
            break;
        // ADD
        case ADD:
            information.first = information.first + information.second;
            break;
        // SUB
        case SUB:
            information.first = information.first - information.second;
            break;
        // AND
        case AND:
            information.first = information.first & information.second;
            break;
        // SLT
        case SLT:
            if ((int64_t)information.first < (int64_t)information.second)
                information.first = 1;
            else
                information.first = 0;
            break;
        // SLL
        case SLL:
            information.first = information.first << (information.second & 0x3F);
            break;
        // SRA
        case SRA:
        {
            int64_t val = (int64_t)information.first;
            int sh = (int)(information.second & 0x3F);
            information.first = (uint64_t)(val >> sh);
            break;
        }
        // LUI
        case LUI:
            information.first = information.second;
            break;
        // if SB SW or SD, reference doc says we need to compute address
        case SB:
        case SW:
        case SD:
        {
            uint64_t address = (uint64_t)(information.first + (int64_t)information.second);
            information.first = address;
            break;
        }
        // BEQ
        case BEQ:
            if (information.first == information.second)
                information.first = (uint64_t)information.third;
            else
                information.first = 0;
            break;
        default:
            break;
    }
    return information;
}

// TODO
info memory(info information)
{
    return information;
}

// TODO
uint64_t writeback(uint64_t PC, info information)
{
    if (information.inst != 0) {
        registers[information.third] = information.first;
    }
    return PC + 4;
}
