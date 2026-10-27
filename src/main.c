#include <stdio.h>

#define intt uint16_t
#define chkzero(index) if (ins_regs[index] == 0) break

intt ins_opcode(intt ins) {return ins >> 11;}
intt ins_reg(intt ins, intt index) {return index < 3 ? ins >> (2 + 3 * (3 - index)) % 8 : 0;}
intt ins_imm(intt ins, intt len) {return ins % (1 << (len - 1));}

int main() {
    intt memory[0x1000] = {0};
    intt reg[0x8] = {0};
    intt pc = 0;
    // load instructions here

    // begin code execution

    while (true) {
        const intt ins = memory[pc];
        const intt ins_regs[3] = {ins_reg(ins, 0), ins_reg(ins, 1), ins_reg(ins, 2)}
        switch (ins_opcode(ins)) {
            case 0: // MOV
                chkzero(0);
                reg[ins_regs[0]] = reg[ins_regs[1]];
                break;
            case 1: // MOVI
                chkzero(0);
                reg[ins_regs[0]] &= 0xff00;
                reg[ins_regs[0]] |= ins_imm(ins, 8);
            case 2: // LUI
                chkzero(0);
                reg[ins_regs[0]] &= 0xff;
                reg[ins_regs[0]] |= ins_imm(ins, 8) << 8;
            case 3: // LD
                chkzero(0);
                reg[ins_regs[0]] = memory[ins_regs[1]];
            case 4: // ST
                memory[ins_regs[1]]
        }
    }

    return 0;
}