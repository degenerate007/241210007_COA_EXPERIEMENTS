# Experiment 4

**Date:** 16-03-2026

---

## AIM

To study the GNU Debugger (GDB) and to analyze the flow of a program using GDB commands.

---

## Software Used

- **GDB (GNU Debugger)** — A command-line debugging tool used to inspect the execution of programs written in C, C++, and other languages.
- **GCC (GNU Compiler Collection)** — Used to compile C programs with debug symbols (`-g` flag).
- **Linux Terminal / Shell**

---

## Theory

### What is GDB?
The GNU Debugger (GDB) is a powerful open-source debugging tool that allows programmers to:
- Pause program execution at specific points (breakpoints)
- Inspect the values of variables and registers
- Step through code line by line
- Analyze the call stack and program flow
- Detect segmentation faults, memory issues, and logical errors

### Compiling for Debugging
To use GDB, the program must be compiled with the `-g` flag to include debug symbols:
```bash
gcc -g program.c -o program
```

### Starting GDB
```bash
gdb ./program
```

### Key GDB Commands

| Command                | Description                                      |
|------------------------|--------------------------------------------------|
| `run` / `r`            | Start the program                                |
| `break <line>` / `b`   | Set a breakpoint at a line number or function    |
| `next` / `n`           | Execute the next line (step over)                |
| `step` / `s`           | Step into a function call                        |
| `continue` / `c`       | Resume execution until next breakpoint           |
| `print <var>` / `p`    | Print the value of a variable                    |
| `print *<ptr>`         | Dereference and print value at a pointer         |
| `print &<var>`         | Print the memory address of a variable           |
| `backtrace` / `bt`     | Show the call stack                              |
| `frame <n>`            | Switch to stack frame number n                   |
| `info breakpoints`     | List all breakpoints                             |
| `delete <num>`         | Delete a specific breakpoint                     |
| `watch <var>`          | Watch a variable and pause when it changes       |
| `list` / `l`           | Display source code around the current line      |
| `info registers`       | Display current values of CPU registers          |
| `x/<n>xw <addr>`       | Examine n words of raw memory at address         |
| `quit` / `q`           | Exit GDB                                         |

---

## Observations

---

### Example 1 — Basic Function Call and Program Flow

**Program (`func.c`):**
```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 10;
    int result = add(x, y);
    printf("Result: %d\n", result);
    return 0;
}
```

**Compilation:**
```bash
gcc -g func.c -o func
```

**GDB Session:**
```
$ gdb ./func
GNU gdb (Ubuntu 12.1) 12.1
(gdb) break main
Breakpoint 1 at 0x1155: file func.c, line 8.

(gdb) run
Starting program: ./func
Breakpoint 1, main () at func.c:8
8           int x = 5, y = 10;

(gdb) next
9           int result = add(x, y);

(gdb) print x
$1 = 5

(gdb) print y
$2 = 10

(gdb) step
add (a=5, b=10) at func.c:4
4           return a + b;

(gdb) backtrace
#0  add (a=5, b=10) at func.c:4
#1  0x0000000000001171 in main () at func.c:9

(gdb) continue
Continuing.
Result: 15
[Inferior 1 (process 5821) exited normally]
```

**Observations:**

| Step | Command        | Output / Observation                                      |
|------|----------------|-----------------------------------------------------------|
|  1   | `break main`   | Breakpoint 1 set at `func.c`, line 8                      |
|  2   | `run`          | Execution pauses at `main()`, line 8                      |
|  3   | `next`         | Moves to line 9 after executing variable declarations     |
|  4   | `print x`      | `$1 = 5`                                                  |
|  5   | `print y`      | `$2 = 10`                                                 |
|  6   | `step`         | Entered `add()` function; paused at line 4                |
|  7   | `backtrace`    | Call stack: `#0 add(a=5, b=10)` → `#1 main()`            |
|  8   | `continue`     | Program resumes; prints `Result: 15` and exits normally   |

---

### Example 2 — Pointers and Memory Addresses

**Program (`pointers.c`):**
```c
#include <stdio.h>

int main() {
    int a = 42;
    int *p = &a;

    printf("Value of a   : %d\n", a);
    printf("Address of a : %p\n", &a);
    printf("Value via ptr: %d\n", *p);

    *p = 100;
    printf("New value of a: %d\n", a);

    return 0;
}
```

**Compilation:**
```bash
gcc -g pointers.c -o pointers
```

**GDB Session:**
```
$ gdb ./pointers
(gdb) break main
Breakpoint 1 at 0x1149: file pointers.c, line 4.

(gdb) run
Breakpoint 1, main () at pointers.c:4
4           int a = 42;

(gdb) next
5           int *p = &a;

(gdb) next
7           printf("Value of a   : %d\n", a);

(gdb) print a
$1 = 42

(gdb) print &a
$2 = (int *) 0x7fffffffe4bc

(gdb) print p
$3 = (int *) 0x7fffffffe4bc

(gdb) print *p
$4 = 42

(gdb) next
(gdb) next
(gdb) next
11          *p = 100;

(gdb) next
12          printf("New value of a: %d\n", a);

(gdb) print a
$5 = 100

(gdb) print *p
$6 = 100

(gdb) x/1xw 0x7fffffffe4bc
0x7fffffffe4bc:    0x00000064

(gdb) continue
Continuing.
Value of a   : 42
Address of a : 0x7fffffffe4bc
Value via ptr: 42
New value of a: 100
[Inferior 1 (process 5834) exited normally]
```

**Observations:**

| Step | Command                 | Output / Observation                                          |
|------|-------------------------|---------------------------------------------------------------|
|  1   | `print a`               | `$1 = 42` — variable holds expected value                     |
|  2   | `print &a`              | `$2 = (int *) 0x7fffffffe4bc` — address of `a` on the stack  |
|  3   | `print p`               | `$3 = (int *) 0x7fffffffe4bc` — `p` stores the same address  |
|  4   | `print *p`              | `$4 = 42` — dereferencing `p` gives the value of `a`         |
|  5   | After `*p = 100`        | `a` is now 100 even though we only wrote through the pointer  |
|  6   | `print a`               | `$5 = 100` — pointer write is reflected in the original var   |
|  7   | `x/1xw 0x7fffffffe4bc`  | `0x00000064` — hex for 100; raw memory confirms the change    |

---

### Example 3 — Recursive Function and Call Stack (Factorial)

**Program (`recursion.c`):**
```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    int num = 4;
    int result = factorial(num);
    printf("Factorial of %d = %d\n", num, result);
    return 0;
}
```

**Compilation:**
```bash
gcc -g recursion.c -o recursion
```

**GDB Session:**
```
$ gdb ./recursion
(gdb) break factorial
Breakpoint 1 at 0x1135: file recursion.c, line 3.

(gdb) run
Breakpoint 1, factorial (n=4) at recursion.c:3
3           if (n == 0)

(gdb) backtrace
#0  factorial (n=4) at recursion.c:3
#1  0x0000000000001174 in main () at recursion.c:11

(gdb) continue
Breakpoint 1, factorial (n=3) at recursion.c:3

(gdb) backtrace
#0  factorial (n=3) at recursion.c:3
#1  0x0000000000001152 in factorial (n=4) at recursion.c:6
#2  0x0000000000001174 in main () at recursion.c:11

(gdb) continue
Breakpoint 1, factorial (n=2) at recursion.c:3

(gdb) continue
Breakpoint 1, factorial (n=1) at recursion.c:3

(gdb) continue
Breakpoint 1, factorial (n=0) at recursion.c:3

(gdb) backtrace
#0  factorial (n=0) at recursion.c:3
#1  0x0000000000001152 in factorial (n=1) at recursion.c:6
#2  0x0000000000001152 in factorial (n=2) at recursion.c:6
#3  0x0000000000001152 in factorial (n=3) at recursion.c:6
#4  0x0000000000001152 in factorial (n=4) at recursion.c:6
#5  0x0000000000001174 in main () at recursion.c:11

(gdb) continue
Continuing.
Factorial of 4 = 24
[Inferior 1 (process 5851) exited normally]
```

**Observations:**

| Call Depth | `n` value | Stack Frames Visible | Return Value |
|------------|-----------|----------------------|--------------|
|     1      |     4     | 2  (`factorial` + `main`) |     —   |
|     2      |     3     | 3  frames            |      —       |
|     3      |     2     | 4  frames            |      —       |
|     4      |     1     | 5  frames            |      —       |
|     5      |     0     | 6  frames (base case)|      1       |
| Unwinding  |     —     | Stack unwinds to `main` |    24     |

**Key Observation:** Each recursive call pushes a new frame onto the call stack. At peak depth (`n=0`) the stack is 6 frames deep. As the recursion unwinds, each frame multiplies its `n` with the value returned from below — `1×1×2×3×4 = 24`.

---

### Example 4 — Array Traversal and Loop Inspection (using `watch`)

**Program (`array.c`):**
```c
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    printf("Sum = %d\n", sum);
    return 0;
}
```

**Compilation:**
```bash
gcc -g array.c -o array
```

**GDB Session:**
```
$ gdb ./array
(gdb) break 7
Breakpoint 1 at 0x1160: file array.c, line 7.

(gdb) run
Breakpoint 1, main () at array.c:7
7           for (int i = 0; i < 5; i++) {

(gdb) watch sum
Watchpoint 2: sum

(gdb) continue
Watchpoint 2, sum
Old value = 0
New value = 10
main () at array.c:7

(gdb) print i
$1 = 0

(gdb) continue
Watchpoint 2, sum
Old value = 10
New value = 30

(gdb) print i
$2 = 1

(gdb) continue
Watchpoint 2, sum
Old value = 30
New value = 60

(gdb) continue
Watchpoint 2, sum
Old value = 60
New value = 100

(gdb) continue
Watchpoint 2, sum
Old value = 100
New value = 150

(gdb) continue
Continuing.
Sum = 150
[Inferior 1 (process 5869) exited normally]
```

**Observations:**

| Iteration (`i`) | `arr[i]` | Old `sum` | New `sum` | Watchpoint Triggered |
|-----------------|----------|-----------|-----------|----------------------|
|        0        |    10    |     0     |    10     |         Yes          |
|        1        |    20    |    10     |    30     |         Yes          |
|        2        |    30    |    30     |    60     |         Yes          |
|        3        |    40    |    60     |   100     |         Yes          |
|        4        |    50    |   100     |   150     |         Yes          |

**Key Observation:** The `watch` command triggered automatically every time `sum` changed, allowing verification of each accumulation step without manually stepping through every line.

---

## Result

The GNU Debugger was successfully used across four different C programs to:
- Trace basic function calls and inspect variable values at runtime
- Examine pointer values, memory addresses, and raw memory contents using `x/xw`
- Observe recursive call stack growth and unwinding using `backtrace`
- Monitor variable changes across loop iterations using `watch`

All observed outputs matched the expected program behaviour, confirming correct execution.

---

## Conclusion

This experiment demonstrates how GDB is an indispensable tool for understanding and debugging C programs at a low level. Different GDB features suit different scenarios — `backtrace` for recursion and stack depth, `print *ptr` and `x/xw` for pointer and memory debugging, `watch` for loop variable tracking, and `step`/`next` for fine-grained line-by-line flow control. Mastering GDB significantly accelerates the debugging process and builds deeper understanding of how C programs execute.