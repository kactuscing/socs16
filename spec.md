# Simple Operation Computing Set 16 (SOCS16)

## Instructions
(keep in mind two's complement is used for signed numbers, e.g. 0x00 is 0, but 0xffff (16 bits) is -1, and in that same vein, 0x8000 is the lowest possible negative number.)


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
| Opcode | Instruction | Description |
| ------ | ----------- | ----------- |
| 0,00   | MOV         | copies src reg contents into dest reg |
| 1,01   | MOVI        | move immediate into lower half of reg |
| 2,02   | LUI         | move immediate into upper half of register |
| 3,03   | LD          | load 16-bit word into register from ram address in register |
| 4,04   | ST          | store 16-bit register into ram address stored in register |
| 5,05   | ADD         | add rd, rs1, rs2:  rd = rs1 + rs2
| 6,06   | ADDI        | addi rd, rs, imm:  rd = rs + imm
| 7,07   | SUB         | sub rd, rs1, rs2:  rd = rs1 - rs2
| 8,010  | SUBI        | subi rd, rs, imm:  rd = rs - imm
| 9,011  | MUL         | mul rd, rs1, rs2:  rd = rs1 * rs2
| 10,012 | IMUL        | imul rd, rs1, rs2: rd = rs1 * rs2 (signed)
| 11,013 | DIV         | div rd, rs1, rs2:  rd = rs1 / rs2 (unsigned int)
| 11,013 | IDIV        | idiv rd, rs1, rs2:  rd = rs1 / rs2 (signed int)
| 12,014 | AND         | bitwise AND
| 13,015 | ANDI        | bitwise AND with immediate
| 14,016 | OR          | bitwise OR
| 15,017 | ORI         | bitwise OR with immediate
| 16,020 | XOR         | bitwise exclusive OR
| 17,021 | NOT         | bitwise NOT
| 18,022 | LSL         | left bit shift
| 19,023 | LSR         | right bit shift
| 21,025 | ASR         | arithmetic right shift
| 22,026 | SLT         | set if less than
| 23,027 | ISLT        | set if less than signed
| 24,030 | SLTI        | set if less than immediate
| 25,031 | ISLTI       | set if less than immediate signed
| 26,032 | BEQ         | branch if equal to
| 27,033 | BNE         | branch if not equal to
| 28,034 | BLT         | branch if less than
| 29,035 | BGE         | branch if greater than
| 30,036 | IBLT        | branch if less than (signed)
| 31,037 | IBGE        | branch if greater than (signed)



##