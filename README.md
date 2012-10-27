# Simple Emulator

## Processor

This "emulates" a fictional 16-bit processor with
* 2 data registers, R1 and R2
* two address registers, A1 and A2
* zero flag Z
* negative flag N
* overflow flag O
* a program counter which holds the memory address of the next instruction to
be executed
* 32768 bytes of memory, 1 byte wide

The processor only performs arithmetic operations on values in the data
registers, while address registers are used to hold
addresses so that data value can be reference indirectly.

There is also a compiler that translates a fictional assembly language into byte
code. test.asm is sample assembly language file.

### Cycles

A cycle is a 3 step process.
1. Fetch the next instruction from memory (indexed by the program counter) and
increment the program counter
2. If the instruction requires fetching additional data, perform this movement 
of data (the destination register for the result of the operation for instance)
3. Perform the operation specified by the instruction, setting any flags to
reflect the state of the result (Z = result is 0, N = result is negative, O =
result is overflow.  Not all flags will have meaning for all operations),
possibly adjusting the program counter in the case of a JMP instruction.

## Assembly language Instruction Set

* LOAD reg1,immSRC
  * load the provided constant value "immSRC" into the specified
register (data or address)
* LOADI reg1,reg2
  * load the data contained in the memory address specified in address register
reg2 into the specified register (data or address)
* STORE reg1,immDEST
  * store the data contained in the specified register (data or address) into
the memory address specified by the provided constant value "immDEST"
* STOREI reg1,reg2
  * store the data contained in the register reg1 (data or address) into the
memory address specified in address register reg2
* JMP immDEST
  * jump to constant valued address "immDEST"
* JMPZ immDEST
  * jump to constant valued address "immDEST" if Z flag is set (i.e.
as result of previous operation)
* JMPN immDEST
  * jump to constant valued address "immDEST" if N flag is set (i.e.
as result of previous operation)
* JMPO immDEST
  * jump to constant valued address "immDEST" if O flag is set (i.e. as
result of previous operation)
* ADD reg1,immSRC
  * add constant value "immSRC" to the value, and store the result, in
data register reg1. Z, N and O flags should be set appropriately as
the result of the operation
* ADDR reg1,reg2
  * add value in data register reg2 to the
value, and store the result, in data register reg1 (reg2 and reg1
cannot be the same register). Z, N and O flags should be set
appropriately as the result of the operation
* SUB reg1,immSRC
  * subtract constant value "immSRC" from the value, and store the
result, in data register reg1. Z, N and O flags should be set
appropriately as the result of the operation
* SUBR reg1,reg2
  * subtract value in data register
reg2 from the value, and store the result, in data register reg1
(reg2 and reg1 can not be the same register). Z, N and O flags
should be set appropriately as the result of the operation
* OUT immSRC
  * output constant value "immSRC" to the screen as an
16-bit signed integer value (i.e. a number).
* OUTC immSRC
  * output constant value "immSRC" to the screen
as an 8-bit unsigned character value (i.e. an ASCII character).
* OUTR reg1
  * output value in data register reg1 as an 16-bit signed
integer value (i.e. a number).
* OUTRC reg1
  * output value in data register reg1 as an 8-bit
unsigned character value (i.e. an ASCII character).
* OUTI reg1
  * output value in the memory address referenced by the provided
address register reg1 as an 16-bit signed integer value (i.e. a
number).
* OUTIC reg1
  * output value value in the memory
address referenced by the provided address register reg1 as an 8-
bit unsigned character value (i.e. an ASCII character).
* HALT
  * The HALT instruction is used to mark the end of program. When your
simulator of the 80d201 processor executes the HALT instruction it
should exit.
* DATA immSRC
  * corresponding memory location will contain the constant
value "immSRC" (this is not really an instruction, and should not
be converted to an instruction in memory, the intention is to allow
this statement to reserve one 2-byte word at this point in memory
for the specified data).

## Assembly language file format
An assembly language files have the following format:

```
1      89+
LABEL   INSTRUCTION OP1[,OP2] # comment (newline)
```

Columns 1 to 7 are reserved for "labels",  named memory locations that will be
resolved by the assembler as it generates the executables to be later loaded
into memory. Labels can be used as "constant values" anywhere one might be
expected. In the process of assembling the source code, all occurrences of
labels are replaced by the memory address of the instruction they precede. This
is convenient for having "named" data storage locations in memory, or as the
targets of JMP instructions. Labels in the source code always resolve to
addresses in memory.  They are case sensitive.

Column 8 must be a space to separate the label from the
instruction.

Instructions start in column 9, and have the format specified in the preceding
section.

The '#' is a comment character and anything appearing after it on a given line
is to be ignored.  Comments are optional.

Each line is terminated by a newline.

## Binary encoding

Instructions, except DATA, are encoded as the following single byte opcodes,
represented in hex.

```
HALT 0x31
LOAD 0x60
LOADI 0x61
STORE 0x62
STOREI 0x63
JMP 0x64
JMPZ 0x65
JMPN 0x66
JMPO 0x67
ADD 0x68
ADDR 0x69
SUB 0x6a
SUBR 0x6b
OUT 0x6c
OUTC 0x6d
OUTR 0x6e
OUTRC 0x6f
OUTI 0x70
OUTIC 0x71
```

The registers are encoded as 2 bit binary representations of the following
values:
```
A1 3
A2 2
R1 1
R2 0
```

Instructions with an immediate argument occupy 4 bytes, those with only
register arguments occupy 2 bytes.

The first byte is the opcode of the instruction

The second byte is used to encode both register arguments, with the first
register argument in the rightmost 2 bits of the byte, and the second in
the leftmost 2 bits of the byte. This means that the middle 4 bits of the
second byte are not used.

For instructions with immediate operands, two bytes following the
encoded register, which may be 0x00, are used to hold the 2 byte data or 
address value used by the instructions.
