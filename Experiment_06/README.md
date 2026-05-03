# Experiment 6

**Date:** 13-04-2026

---

## AIM

To design and implement a 4-bit Common Bus System using Multiplexers and Registers on Logisim.

---

## Software Used

- **Logisim** — A graphical tool for designing and simulating digital logic circuits, including registers and multiplexers.

---

## Theory

### What is a Common Bus System?
A **Common Bus System** is a shared communication pathway that allows multiple registers to transfer data to one another efficiently. Instead of direct point-to-point connections between every pair of registers, all registers connect to a single shared bus. Only one register can **drive** the bus at a time, while others can **read** from it.

### Components Used

#### 1. Register
A register is a small, fast storage element made of D flip-flops. A **4-bit register** stores 4 bits of data and can:
- **Load** data from the bus (when load signal is HIGH)
- **Hold** its current value (when load signal is LOW)
- **Output** its stored value onto the bus (when output enable is HIGH)

#### 2. Multiplexer (MUX)
A Multiplexer selects one of several inputs and forwards it to the output based on select lines. In a common bus system:
- An **8×1 MUX** (or a bank of them for 4-bit data) selects which register's data is placed on the bus.
- Select lines **S1, S0** choose which register drives the bus.

### Architecture

Consider **4 registers: R0, R1, R2, R3** and a **4-bit wide common bus**:

```
        +--------+   +--------+   +--------+   +--------+
        |   R0   |   |   R1   |   |   R2   |   |   R3   |
        +---+----+   +---+----+   +---+----+   +---+----+
            |            |            |            |
            +------------+------------+------------+
                                  |
                          4-bit MUX Bank
                         (Select: S1, S0)
                                  |
                          4-bit Common Bus
                                  |
                    (Any register can read from bus)
```

### MUX Select Logic

| S1 | S0 | Register Driving the Bus |
|----|----|--------------------------|
|  0 |  0 |  R0                      |
|  0 |  1 |  R1                      |
|  1 |  0 |  R2                      |
|  1 |  1 |  R3                      |

### Data Transfer Operations
Using the common bus, data transfers between registers are controlled by:
1. **Selecting the source register** via MUX select lines (S1, S0)
2. **Enabling the load** signal of the destination register

Example: To transfer R1 → R3:
- Set S1=0, S0=1 (selects R1 to drive the bus)
- Assert Load signal of R3
- On the clock edge, R3 latches the value from the bus

---

## Observations

### MUX Output Verification

| S1 | S0 | Source Register | Data on Bus (4-bit)  | Observed Output |
|----|----|-----------------|----------------------|-----------------|
|  0 |  0 |       R0        |       1010           |      1010       |
|  0 |  1 |       R1        |       0110           |      0110       |
|  1 |  0 |       R2        |       1101           |      1101       |
|  1 |  1 |       R3        |       0011           |      0011       |

### Register Transfer Verification

| Operation   | Source (S1,S0) | Destination Load | Data Before      | Data After       |
|-------------|----------------|------------------|------------------|------------------|
| R0 → R1     | (0,0)          | R1 Load = 1      | R1 = 0000        | R1 = 1010        |
| R1 → R3     | (0,1)          | R3 Load = 1      | R3 = 1111        | R3 = 0110        |
| R2 → R0     | (1,0)          | R0 Load = 1      | R0 = 1010        | R0 = 1101        |
| R3 → R2     | (1,1)          | R2 Load = 1      | R2 = 1101        | R2 = 0011        |

---

## Result

A 4-bit Common Bus System was successfully designed and implemented in Logisim using multiplexers and registers. Data transfer between registers via the shared bus was verified for all combinations of MUX select lines.

---

## Conclusion

This experiment demonstrates the concept of a shared bus architecture, which is fundamental to the internal organization of CPUs. The use of a MUX-based selection mechanism allows efficient and organized data transfer between multiple registers using a single common bus, reducing wiring complexity and enabling modular design.