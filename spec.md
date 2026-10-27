# Simple Operation Computing Set 16 (SOCS16)

## Instructions
(keep in mind two's complement is used for signed numbers, e.g. 0x0000 is 0, but 0xffff (16 bits) is -1, and in that same vein, 0x8000 is the lowest possible negative number, that being -32768)

## Branches
All branches are done with program counter relatives. The register can thus change the program counter by +/- 32768 instructions.

## Registers
1. `r0/zero`: **Always set to zero.** Reading returns zeroes, writing does nothing.
2. `r1/at`: **Assembler Temporary.** Used in cases, for instance, where a 16-bit immediate is needed. Something like `MOVI at, 01;LUI at, 02`. Then, `at` is now essentially an immediate of 012, where we can acheive a full 16 bits in an immediate.
3. `r2/v0`: **Return Value.** Functions should *always* place output data here.
4. `r3/a0`: **Function Argument.** Arguments should ideally be placed here.
5. `r4/t0`: **Temporary Data.** Scratchpad memory for calculations.
6. `r5/t1`: **More Temporary Data.** In the likely event you needed more and don't like the stack.
7. `r6/lr`: **Link Register.** Stores the return address for calling a function.
8. `r7/sp`: **Stack Pointer.** Points to the current top of the memory stack.

## Opcodes
32 ($2^5$) different opcodes. 00 to 037, 0x0 to 0x1f, etc.
| Opcode | Instruction | Description                                                 | Syntax |
| ------ | ----------- | -----------                                                 | ------ |
| 0,00   | MOV         | copies src reg contents into dest reg                       | MOV rdd\[dest], rs1\[src]
| 1,01   | MOVI        | move immediate into lower half of reg                       | MOVI rdd\[dest], 0x34\[8b immediate]
| 2,02   | LUI         | move immediate into upper half of register                  | LUI rdd\[dest], 0x12\[8b immediate]
| 3,03   | LD          | load 16-bit word into register from ram address in register | LD rdd\[dest], rs1\[address]
| 4,04   | ST          | store 16-bit register into ram address stored in register   | ST rdd\[address], rs1\[src]
| 5,05   | ADD         | add rd, rs1, rs2:  rd = rs1 + rs2                           | ADD rdd\[dest], rs1\[src], rs2\[src]
| 6,06   | ADDI        | addi rd, rs, imm:  rd = rs + imm                            | ADDI rdd\[dest], rs1\[src], rs2\[src]
| 7,07   | SUB         | sub rd, rs1, rs2:  rd = rs1 - rs2                           | SUB rdd\[dest], rs1\[src], rs2\[src]
| 8,010  | SUBI        | subi rd, rs, imm:  rd = rs - imm                            | SUBI rdd\[dest], rs1\[src], rs2\[src]
| 9,011  | MUL         | mul rd, rs1, rs2:  rd = rs1 * rs2                           | MUL rdd\[dest], rs1\[src], rs2\[src]
| 10,012 | IMUL        | imul rd, rs1, rs2: rd = rs1 * rs2 (signed)                  | IMUL rdd\[dest], rs1\[src], rs2\[src]
| 11,013 | DIV         | div rd, rs1, rs2:  rd = rs1 / rs2 (unsigned int)            | DIV rdd\[dest], rs1\[src], rs2\[src]
| 12,014 | IDIV        | idiv rd, rs1, rs2:  rd = rs1 / rs2 (signed int)             | IDIV rdd\[dest], rs1\[src], rs2\[src]
| 13,015 | AND         | bitwise AND                                                 | AND rdd\[dest], rs1\[src], rs2\[src]
| 14,016 | OR          | bitwise OR                                                  | OR rdd\[dest], rs1\[src], rs2\[src]
| 14,017 | XOR         | bitwise exclusive OR                                        | XOR rdd\[dest], rs1\[src], rs2\[src]
| 15,020 | NOT         | bitwise NOT                                                 | NOT rdd\[dest], rs1\[src], rs2\[src]
| 16,021 | LSL         | left bit shift                                              | LSR rdd\[dest]
| 17,022 | LSR         | right bit shift                                             | LSL rdd\[dest]
| 19,023 | ASR         | arithmetic right shift                                      | ASR rdd\[dest]
| 20,024 | ASL         | arithmetic left shift                                       | ASL rdd\[dest]
| 21,025 | SLT         | sets rd to 1 if rs1 < rs2 else set to 0 (signed)            | SLT rdd\[dest], rs1\[src], rs2\[src]
| 22,026 | SLTU        | sets rd to 1 if rs1 < rs2 else set to 0 (unsigned)          | SLTU rdd\[dest], rs1\[src], rs2\[src]
| 23,027 | SLTI        | sets rd to 1 if rs1 < immediate else set to 0 (signed)      | SLTI rdd\[dest], rs1\[src], imm\[5b immediate]
| 24,030 | SLTIU       | sets rd to 1 if rs1 < immediate else set to 0 (unsigned)    | SLTIU rdd\[dest], rs1\[src], imm\[5b immediate]
| 25,031 | BEQ         | branch if equal to                                          | BEQ rdd\[program counter relative], rs1\[src], rs2\[src]
| 26,032 | BNE         | branch if not equal to                                      | BNE rdd\[program counter relative], rs1\[src], rs2\[src]
| 27,033 | BLT         | branch if less than                                         | BLT rdd\[program counter relative], rs1\[src], rs2\[src]
| 28,034 | BGE         | branch if greater than                                      | BGE rdd\[program counter relative], rs1\[src], rs2\[src]
| 29,035 | IBLT        | branch if less than (signed)                                | IBLT rdd\[program counter relative], rs1\[src], rs2\[src]
| 30,036 | IBGE        | branch if greater than (signed)                             | IBGE rdd\[program counter relative], rs1\[src], rs2\[src]
| 31,037 | SYS         | syscall                                                     | SYS

## syscalls :sob: we have 2^16 of them ahahh

0x0 exit
0x1 error
0x2 read stdin   r2/v0 output buffer address    r3/a0 buffer size (bytes)
0x3 write stdin  r2/v0 input buffer address     r3/a0 number of bytes to output from starting position

## Conventions

Preferably all program memory should begin at 0x8000, and the instructions should be from 0x0 to 0x7fff. Program mem should ideally be from 0x8000 to 0x10000

##
