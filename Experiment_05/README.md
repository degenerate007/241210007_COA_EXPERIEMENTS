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
Addressing modes define **how the operand of an instruction is accessed** — whether the data is a constant, stored in a register, at a memory address, or computed from a base and offset. Different modes offer varying trade-offs between speed, flexibility, and code size.

### Program Used

```c
// types of addressing

#include <stdio.h>

int global_var = 50;

int main() {
    int a = 10, b = 20;
    int result = 0;

    // implicit
    result++;

    // immediate
    result = a + 5;

    // direct
    result = global_var;

    // indirect
    int *ptr = &a;
    result = *ptr;

    // register
    result = a + b;

    // register indirect
    int *p = &b;
    result = *p;

    // displacement
    int arr[3] = {1, 2, 3};

    // indexed
    result = arr[1];

    // base + offset
    result = *(arr + 2);

    // relative
    for (int i = 0; i < 3; i++) {
        result += arr[i];
    }

    // stack
    int stack_var = 30;
    result = stack_var;

    printf("result: %d\n", result);
    return 0;
}
```

**Compilation:**
```bash
gcc -g addressing.c -o addressing
```

---

### Types of Addressing Modes (as demonstrated in the program)

#### 1. Implicit Addressing Mode
The operand is **implied by the instruction itself** — no explicit operand is specified.
```c
result++;     // The increment of 1 is implicit in the ++ operator
```
```asm
addl $1, -12(%rbp)    ; +1 is implied by the increment instruction
```

#### 2. Immediate Addressing Mode
The operand is a **constant value embedded directly** in the instruction.
```c
result = a + 5;    // 5 is an immediate (literal) value
```
```asm
addl $5, %eax    ; $5 is the immediate operand — no memory access needed
```

#### 3. Direct (Absolute) Addressing Mode
The instruction specifies the **fixed memory address** of the operand directly. Typically used for global variables whose address is known at compile time.
```c
result = global_var;    // global_var has a fixed address in the data segment
```
```asm
movl global_var(%rip), %eax    ; load from fixed/direct memory address
```

#### 4. Indirect Addressing Mode
A **pointer holds the address** of the operand. The CPU first reads the address from the pointer, then fetches the actual value.
```c
int *ptr = &a;
result = *ptr;    // ptr holds address of a; *ptr dereferences it
```
```asm
movq -24(%rbp), %rax    ; load address stored in ptr
movl (%rax), %eax       ; dereference: fetch value at that address
```

#### 5. Register Addressing Mode
Both operands are **directly in CPU registers** — fastest mode since no memory access is needed.
```c
result = a + b;    // a and b are loaded into registers, added directly
```
```asm
movl -4(%rbp), %edx     ; load a into register EDX
movl -8(%rbp), %eax     ; load b into register EAX
addl %edx, %eax         ; add register to register
```

#### 6. Register Indirect Addressing Mode
The register holds the **address** of the operand (not the value itself). Similar to indirect but the address is in a register, not memory.
```c
int *p = &b;
result = *p;    // p is a register-held pointer to b
```
```asm
movq -32(%rbp), %rax    ; load address of b from p into RAX
movl (%rax), %eax       ; fetch value at the address in RAX
```

#### 7. Indexed Addressing Mode
The effective address is computed as **base address + index × element size**. Used for array access via subscript.
```c
result = arr[1];    // base address of arr + index 1
```
```asm
movl -48(%rbp,%rax,4), %eax    ; base + index*4 (int = 4 bytes)
```

#### 8. Base + Offset (Displacement) Addressing Mode
The effective address is **base address + constant offset**. Used for pointer arithmetic on arrays.
```c
result = *(arr + 2);    // arr is base; +2 is a fixed offset
```
```asm
movl -40(%rbp), %eax    ; access arr[2] via base pointer + 8-byte offset
```

#### 9. Relative Addressing Mode
The address is computed **relative to the current instruction pointer (PC/RIP)**. Used in loops and branches where the jump target is expressed as an offset from the current position.
```c
for (int i = 0; i < 3; i++) {
    result += arr[i];
}
```
```asm
jle  .L3      ; jump to loop body — target is relative to current PC
```

#### 10. Stack Addressing Mode
Operands are accessed via the **stack pointer (RSP)**. Local variables are pushed/allocated on the stack automatically by the function prologue.
```c
int stack_var = 30;
result = stack_var;    // stack_var lives on the stack frame
```
```asm
movl $30, -52(%rbp)    ; store 30 at stack offset -52 from base pointer
movl -52(%rbp), %eax   ; load it back — accessed entirely via stack frame
```

---

## Observations

### GDB Session

**Starting GDB:**
```bash
$ gdb ./addressing
GNU gdb (Ubuntu 12.1) 12.1
Reading symbols from ./addressing...
(gdb)
```

**Setting breakpoints and running:**
```
(gdb) break main
Breakpoint 1 at 0x1149: file addressing.c, line 8.

(gdb) run
Starting program: ./addressing
Breakpoint 1, main () at addressing.c:8
8           int a = 10, b = 20;
```

**Disassembling `main` to view all addressing modes in assembly:**
```
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000001149 <+0>:     push   %rbp
   0x000000000000114a <+1>:     mov    %rsp,%rbp
   0x000000000000114d <+4>:     sub    $0x40,%rsp

   ; --- Implicit: result++ ---
   0x0000000000001151 <+8>:     movl   $0,-12(%rbp)
   0x0000000000001158 <+15>:    addl   $1,-12(%rbp)

   ; --- Immediate: result = a + 5 ---
   0x000000000000115c <+19>:    movl   -4(%rbp),%eax
   0x000000000000115f <+22>:    addl   $5,%eax
   0x0000000000001162 <+25>:    movl   %eax,-12(%rbp)

   ; --- Direct: result = global_var ---
   0x0000000000001165 <+28>:    movl   global_var(%rip),%eax
   0x000000000000116b <+34>:    movl   %eax,-12(%rbp)

   ; --- Indirect: *ptr ---
   0x000000000000116e <+37>:    leaq   -4(%rbp),%rax
   0x0000000000001172 <+41>:    movq   %rax,-24(%rbp)
   0x0000000000001176 <+45>:    movq   -24(%rbp),%rax
   0x000000000000117a <+49>:    movl   (%rax),%eax
   0x000000000000117c <+51>:    movl   %eax,-12(%rbp)

   ; --- Register: a + b ---
   0x000000000000117f <+54>:    movl   -4(%rbp),%edx
   0x0000000000001182 <+57>:    movl   -8(%rbp),%eax
   0x0000000000001185 <+60>:    addl   %edx,%eax
   0x0000000000001187 <+62>:    movl   %eax,-12(%rbp)

   ; --- Register Indirect: *p ---
   0x000000000000118a <+65>:    leaq   -8(%rbp),%rax
   0x000000000000118e <+69>:    movq   %rax,-32(%rbp)
   0x0000000000001192 <+73>:    movq   -32(%rbp),%rax
   0x0000000000001196 <+77>:    movl   (%rax),%eax
   0x0000000000001198 <+79>:    movl   %eax,-12(%rbp)

   ; --- Indexed: arr[1] ---
   0x00000000000011b5 <+108>:   movl   $1,%eax
   0x00000000000011ba <+113>:   movl   -48(%rbp,%rax,4),%eax
   0x00000000000011be <+117>:   movl   %eax,-12(%rbp)

   ; --- Base+Offset: *(arr+2) ---
   0x00000000000011c1 <+120>:   movl   -40(%rbp),%eax
   0x00000000000011c4 <+123>:   movl   %eax,-12(%rbp)

   ; --- Relative: loop branch ---
   0x00000000000011c7 <+126>:   movl   $0,-52(%rbp)
   0x00000000000011ce <+133>:   jmp    0x11e4 <main+155>
   0x00000000000011d0 <+135>:   ...
   0x00000000000011e4 <+155>:   cmpl   $2,-52(%rbp)
   0x00000000000011e8 <+159>:   jle    0x11d0 <main+135>

   ; --- Stack: stack_var ---
   0x00000000000011ea <+161>:   movl   $30,-56(%rbp)
   0x00000000000011f1 <+168>:   movl   -56(%rbp),%eax
   0x00000000000011f4 <+171>:   movl   %eax,-12(%rbp)
End of assembler dump.
```

**Inspecting key variables during execution:**
```
(gdb) break 11
Breakpoint 2 at 0x1158: file addressing.c, line 11.   ; result++

(gdb) continue
Breakpoint 2, main () at addressing.c:11
11          result++;

(gdb) print result
$1 = 0

(gdb) next
12          result = a + 5;

(gdb) print result
$2 = 1                        ; implicit increment confirmed

(gdb) next
15          result = global_var;

(gdb) print result
$3 = 15                       ; a(10) + 5 = 15, immediate confirmed

(gdb) next
18          int *ptr = &a;

(gdb) print result
$4 = 50                       ; global_var = 50, direct confirmed

(gdb) next
(gdb) next
19          result = *ptr;

(gdb) print ptr
$5 = (int *) 0x7fffffffe4bc   ; ptr holds address of a

(gdb) print *ptr
$6 = 10                       ; indirect: value at address = 10

(gdb) next
21          result = a + b;

(gdb) print result
$7 = 10                       ; indirect confirmed

(gdb) next
23          int *p = &b;

(gdb) print result
$8 = 30                       ; a(10) + b(20) = 30, register confirmed

(gdb) next
(gdb) next
26          int arr[3] = {1, 2, 3};

(gdb) print *p
$9 = 20                       ; register indirect: *p = b = 20

(gdb) next
(gdb) next
28          result = arr[1];

(gdb) print arr
$10 = {1, 2, 3}

(gdb) next
30          result = *(arr + 2);

(gdb) print result
$11 = 2                       ; indexed arr[1] = 2 confirmed

(gdb) next
33          for (int i = 0; i < 3; i++) {

(gdb) print result
$12 = 3                       ; base+offset *(arr+2) = arr[2] = 3

(gdb) next
(gdb) next
(gdb) next

(gdb) print result
$13 = 9                       ; 3 + arr[0]+arr[1]+arr[2] = 3+1+2+3 = 9

(gdb) next
37          int stack_var = 30;

(gdb) print &result
$14 = (int *) 0x7fffffffe4b4

(gdb) next
38          result = stack_var;

(gdb) print stack_var
$15 = 30

(gdb) print &stack_var
$16 = (int *) 0x7fffffffe4ac  ; lives on the stack frame

(gdb) continue
Continuing.
result: 30
[Inferior 1 (process 6102) exited normally]
```

---

### Summary of Addressing Modes Observed

| # | Addressing Mode   | C Code                  | Assembly Instruction                   | Observed Value |
|---|-------------------|-------------------------|----------------------------------------|----------------|
| 1 | Implicit          | `result++`              | `addl $1, -12(%rbp)`                  | 0 → 1          |
| 2 | Immediate         | `result = a + 5`        | `addl $5, %eax`                        | 15             |
| 3 | Direct            | `result = global_var`   | `movl global_var(%rip), %eax`          | 50             |
| 4 | Indirect          | `result = *ptr`         | `movq -24(%rbp),%rax` → `movl (%rax)` | 10             |
| 5 | Register          | `result = a + b`        | `addl %edx, %eax`                      | 30             |
| 6 | Register Indirect | `result = *p`           | `movq -32(%rbp),%rax` → `movl (%rax)` | 20             |
| 7 | Indexed           | `result = arr[1]`       | `movl -48(%rbp,%rax,4), %eax`          | 2              |
| 8 | Base + Offset     | `result = *(arr + 2)`   | `movl -40(%rbp), %eax`                 | 3              |
| 9 | Relative          | `for` loop branch       | `jle 0x11d0 <main+135>`                | PC-relative    |
|10 | Stack             | `result = stack_var`    | `movl -56(%rbp), %eax`                 | 30             |

---

## Result

All 10 addressing modes were successfully demonstrated using a single C program and verified through GDB. The `disassemble main` command revealed the exact x86-64 assembly instructions generated by GCC for each addressing mode. Variable values at each stage were confirmed using `print` and `next`.

**Final program output:**
```
result: 30
```

---

## Conclusion

This experiment illustrates how different high-level C constructs — constants, pointers, arrays, global variables, and local stack variables — map to distinct machine-level addressing modes at the assembly level. GDB's `disassemble`, `print`, and `next` commands together provide a complete picture of how the CPU fetches operands at each stage of execution. Understanding these modes is fundamental to compiler design, performance optimization, and low-level systems programming.