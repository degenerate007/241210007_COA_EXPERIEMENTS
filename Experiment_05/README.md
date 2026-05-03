# Experiment 5

**Date:** 06-04-2026

---

## AIM

To study different addressing modes of instructions by analyzing the execution of a C program using the GNU Debugger (GDB).

---

## Software Used

- **GDB (GNU Debugger)** — Used to inspect assembly instructions and memory addressing during program execution.
- **GCC (GNU Compiler Collection)** — Used to compile C programs with debug symbols (`-g` flag).
- **Linux Terminal / Shell**

---

## Theory

### What are Addressing Modes?
Addressing modes define how the operand (data) of an instruction is accessed. They determine whether the data is directly available, stored in a register, or located at a memory address. Different addressing modes offer trade-offs between speed and flexibility.

### Types of Addressing Modes

#### 1. Immediate Addressing Mode
The operand value is **directly specified** in the instruction itself.
```c
int x = 5;   // 5 is an immediate value
```
```asm
MOV EAX, 5   ; Operand is the constant 5
```

#### 2. Register Addressing Mode
The operand is stored in a **CPU register**.
```asm
MOV EAX, EBX  ; Copy value from EBX to EAX
```

#### 3. Direct (Absolute) Addressing Mode
The instruction specifies the **memory address** of the operand directly.
```asm
MOV EAX, [0x1234]  ; Load value from memory address 0x1234
```

#### 4. Indirect Addressing Mode
The operand's address is stored in a **register**. The register acts as a pointer.
```c
int arr[] = {1, 2, 3};
int *p = arr;
printf("%d", *p);  // Indirect: address is in pointer p
```
```asm
MOV EAX, [EBX]  ; EBX holds the address of the operand
```

#### 5. Register Relative (Base + Offset) Addressing Mode
The effective address is calculated as the sum of a **base register** and a **constant offset**.
```c
arr[2]  // Base address of arr + offset of 2 elements
```
```asm
MOV EAX, [EBX + 8]  ; EBX = base, 8 = offset
```

#### 6. Indexed Addressing Mode
The effective address is calculated using a **base register + index register**.
```asm
MOV EAX, [EBX + ESI]
```

### Observing Addressing Modes in GDB
Using the `disassemble` command in GDB, assembly instructions generated from a C program can be inspected to identify which addressing modes are being used at the machine level.
```bash
(gdb) disassemble main
(gdb) info registers
(gdb) x/10i $pc       # Examine 10 instructions at current PC
```

---

## Observations

### Sample C Program
```c
#include <stdio.h>

int main() {
    int a = 10;           // Immediate
    int b = a;            // Register
    int arr[3] = {1,2,3};
    int *p = arr;         // Indirect
    int val = arr[2];     // Register Relative

    printf("%d %d %d\n", b, *p, val);
    return 0;
}
```

### Addressing Modes Observed via GDB

| Addressing Mode       | Assembly Instruction Observed       | Description                                     |
|-----------------------|-------------------------------------|-------------------------------------------------|
| Immediate             | `movl $10, -4(%rbp)`               | Constant 10 stored directly into stack location  |
| Register              | `mov %eax, %ebx`                   | Value copied from register EAX to EBX            |
| Direct                | `mov 0x601040, %eax`               | Value loaded from fixed memory address           |
| Indirect              | `mov (%rax), %eax`                 | Address in RAX used to fetch the operand         |
| Register Relative     | `mov -0x8(%rbp), %eax`             | Stack variable accessed via base pointer offset  |
| Indexed               | `mov (%rbx,%rcx,4), %eax`          | Array element accessed via base + index×scale    |

_(Disassemble the program in GDB and record the assembly instructions for each addressing mode.)_

### GDB Commands Used

| Command               | Purpose                          | Output Observed                              |
|-----------------------|----------------------------------|----------------------------------------------|
| `disassemble main`    | View assembly of main function   | Lists all x86 instructions for `main`        |
| `info registers`      | View current register values     | EAX=0xA, EBP=0x7fffffffe4d0, etc.            |
| `x/i $pc`             | Examine instruction at PC        | `movl $0xa, -0x4(%rbp)` (immediate mode)     |
| `print &a`            | Print address of variable a      | `$1 = (int *) 0x7fffffffe4cc`                |
| `print arr`           | Print address of array           | `$2 = (int [3]) {1, 2, 3}`                   |

---

## Result

Different addressing modes were successfully identified by disassembling a C program in GDB. Immediate, Register, Indirect, and Register Relative addressing modes were observed in the generated assembly instructions.

---

## Conclusion

This experiment illustrates how high-level C constructs map to different machine-level addressing modes. Understanding addressing modes is fundamental to assembly programming, compiler design, and low-level performance optimization. GDB serves as an effective tool for inspecting these modes at runtime.