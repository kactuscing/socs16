#include <stdint.h>
#include <stdio.h>

#define nt int16_t
#define ut uint16_t
#define branch(program_counter, counter_change) if (counter_change < 0) {program_counter -= (ut)counter_change & 0x7ff;} else {program_counter += (ut)counter_change & 0x7ff;}


ut ins_opcode(ut ins) {return ins >> 11;}
ut ins_reg(ut ins, ut index) {return index < 3 ? (ins >> (2 + 3 * (2 - index))) % 8 : 0;}
ut ins_imm(ut ins, ut len) {return ins % (1 << (len));}

int syscall(nt (*mem)[0x10000], nt (*reg)[0x8]) {
    switch ((*reg)[1]) {
        case 0:
            printf("Process exited with code %d", (*reg[2]), stdout);
            return 1;
        case 1:
            printf("Process failed with code %d", (*reg)[2], stderr);
            return 1;
        case 2: {
            ut buf_size = (ut)(*reg)[3];
            ut address = (ut)(*reg)[2];
            char buf[buf_size];
            fgets(buf, buf_size, stdin);
            for (ut i = 0; i < buf_size; i++) 
                (*mem)[address+i] = buf[i];
            return 0;
        }
        case 3: {
            ut buf_size = (ut)(*reg)[3];
            ut address = (ut)(*reg)[2];
            char buf[buf_size];
            for (ut i = 0; i < buf_size; i++) 
                buf[i] = (*mem)[address+i];
            printf("%s",buf);
            return 0;
        }
        default:
            printf("Process failed: opcode %d not found.", (*reg)[1], stderr);
            return 1;
    }

    return 0;
}

int main() {
    nt memory[0x10000] = {0};
    nt reg[0x8] = {0};
    ut pc = 0;
    // load instructions here
    /*
    print the char A
    MOVI r1 42 VALID
    0000100100101010
    LUI r2 0x80 VALID
    0001001010000000
    ST r1 r2 VALID
    0010000101000000
    MOV r1 r0 VALID
    0000000100000000
    ADDI r2 r2 1
    0011001001000001
    ST r1 r2
    0010000101000000
    MOVI r2 0
    0000101000000000
    MOVI r3 2
    0000101100000010
    MOV r1 r0
    0000000100000000
    MOVI r1 3
    0000100100000011
    SYS
    1111100000000000
    MOV r1 r0
    0000000100000000
    SYS
    1111100000000000
    */

    memory[0] = 2346;
    memory[1] = 4736;
    memory[2] = 8512;
    memory[3] = 256;
    memory[4] = 12865;
    memory[5] = 8512;
    memory[6] = 2560;
    memory[7] = 2818;
    memory[8] = 256;
    memory[9] = 2307;
    memory[10] = 2880;
    memory[11] = -2048;
    memory[12] = 256;
    memory[13] = -2048;
    
    // begin code execution

    for (int i = 0; i < 14; i++) {
        const ut ins = memory[pc];
        const ut ins_regs[3] = {ins_reg(ins, 0), ins_reg(ins, 1), ins_reg(ins, 2)};
        printf("opcode %u with regs %u and %u, 8b imm %u, 5b imm %u\n", ins_opcode(ins), ins_regs[0], ins_regs[1], ins_imm(ins, 8), ins_imm(ins, 5));
        if (ins_regs[0] == 0 && ins_opcode(ins) != 31) switch (ins_opcode(ins)) {
            case 0: // MOV
                reg[ins_regs[0]] = reg[ins_regs[1]];
                break;
            case 1: // MOVI
                reg[ins_regs[0]] &= 0xff00;
                reg[ins_regs[0]] |= ins_imm(ins, 8);
                break;
            case 2: // LUI
                reg[ins_regs[0]] &= 0xff;
                reg[ins_regs[0]] |= ins_imm(ins, 8) << 8;
                break;
            case 3: // LD
                reg[ins_regs[0]] = memory[ins_regs[1]];
                break;
            case 4: // ST
                memory[ins_regs[1]] = reg[ins_regs[0]];
                break;
            case 5: // ADD
                reg[ins_regs[0]] = reg[ins_regs[1]] + reg[ins_regs[2]];
                break;
            case 6: // ADDI
                reg[ins_regs[0]] = reg[ins_regs[1]] + ins_imm(ins, 5);
                break;
            case 7: // SUB
                reg[ins_regs[0]] = reg[ins_regs[1]] - reg[ins_regs[2]];
                break;
            case 8: // SUBI
                reg[ins_regs[0]] = reg[ins_regs[1]] - ins_imm(ins, 5);
                break;
            case 9: // MUL
                reg[ins_regs[0]] = reg[ins_regs[1]] * reg[ins_regs[2]];
                break;
            case 10: // IMUL
                reg[ins_regs[0]] = (ut)reg[ins_regs[1]] * (ut)reg[ins_regs[2]];
                break;
            case 11: // DIV
                reg[ins_regs[0]] = reg[ins_regs[1]] / reg[ins_regs[2]];
                break;
            case 12: // IDIV
                reg[ins_regs[0]] = (ut)reg[ins_regs[1]] / (ut)reg[ins_regs[2]];
                break;
            case 13: // AND
                reg[ins_regs[0]] = reg[ins_regs[1]] & reg[ins_regs[2]];
                break;
            case 14: // OR
                reg[ins_regs[0]] = reg[ins_regs[1]] | reg[ins_regs[2]];
                break;
            case 15: // XOR
                reg[ins_regs[0]] = reg[ins_regs[1]] ^ reg[ins_regs[2]];
                break;
            case 16: // NOT
                reg[ins_regs[0]] = ~reg[ins_regs[1]];
                break;
            case 17: // LSL
                reg[ins_regs[0]] = reg[ins_regs[1]] << 1;
                break;
            case 18: // LSR
                reg[ins_regs[0]] = (ut)reg[ins_regs[1]] >> 1;
                break;
            case 19: // ASR
                reg[ins_regs[0]] = (nt)reg[ins_regs[1]] >> 1;
                break;
            case 20: // ASL
                reg[ins_regs[0]] = reg[ins_regs[1]] << 1;
                break;
            case 21: // SLT
                reg[ins_regs[0]] = reg[ins_regs[1]] < reg[ins_regs[2]];
                break;
            case 22: // SLTU
                reg[ins_regs[0]] = (ut)reg[ins_regs[1]] < (ut)reg[ins_regs[2]];
                break;
            case 23: // SLTI
                reg[ins_regs[0]] = reg[ins_regs[1]] < ins_imm(ins, 5);
                break;
            case 24: // SLTIU
                reg[ins_regs[0]] = (ut)reg[ins_regs[1]] < (ut)ins_imm(ins, 5);
                break;
            case 25: // BEQ
                if (reg[ins_regs[1]] == reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 26: // BNE
                if (reg[ins_regs[1]] != reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 27: // BLT
                if (reg[ins_regs[1]] < reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 28: // BGE
                if (reg[ins_regs[1]] > reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 29: // IBLT
                if ((ut)reg[ins_regs[1]] < (ut)reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 30: // IBGE
                if ((ut)reg[ins_regs[1]] > (ut)reg[ins_regs[2]]) {branch(pc, ins_regs[0])}
                break;
            case 31: { // SYS
                // syscall logic
                int ret = syscall(&memory, &reg);
                if (ret == 1) return 0;
            }
            default:
                printf("Unknown instruction: %d\n", ins_opcode(ins));
                return 1;
        }
        pc++;
    }
    printf("char %c", memory[0x8000]);
    return 0;
}

/*
8,034 | BGE         | branch if greater than                                      | BGE rdd\[program counter relative], rs1\[src], rs2\[src]
| 29,035 | IBLT        | branch if less than (unsigned)                                | IBLT rdd\[program counter relative], rs1\[src], rs2\[src]
| 30,036 | IBGE        | branch if greater than (unsigned)                             | IBGE rdd\[program counter relative], rs1\[src], rs2\[src]
| 31,037 | SYS         | syscall                                                     | SYS

*/