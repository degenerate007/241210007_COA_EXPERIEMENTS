# Experiment 1

**Date:** 19-01-2026

---

## AIM

To design and verify Half Adder, Full Adder, and 4-bit Adder on Logisim.

---

## Software Used

- **Logisim** — A graphical tool for designing and simulating digital logic circuits.

---

## Theory

### Half Adder
A Half Adder is a combinational circuit that adds two single-bit binary numbers. It produces two outputs:
- **Sum (S):** XOR of the two inputs → `S = A ⊕ B`
- **Carry (C):** AND of the two inputs → `C = A · B`

| A | B | Sum | Carry |
|---|---|-----|-------|
| 0 | 0 |  0  |   0   |
| 0 | 1 |  1  |   0   |
| 1 | 0 |  1  |   0   |
| 1 | 1 |  0  |   1   |

### Full Adder
A Full Adder adds three single-bit binary numbers (A, B, and Carry-in). It produces:
- **Sum (S):** `S = A ⊕ B ⊕ Cin`
- **Carry-out (Cout):** `Cout = (A · B) + (Cin · (A ⊕ B))`

| A | B | Cin | Sum | Cout |
|---|---|-----|-----|------|
| 0 | 0 |  0  |  0  |   0  |
| 0 | 0 |  1  |  1  |   0  |
| 0 | 1 |  0  |  1  |   0  |
| 0 | 1 |  1  |  0  |   1  |
| 1 | 0 |  0  |  1  |   0  |
| 1 | 0 |  1  |  0  |   1  |
| 1 | 1 |  0  |  0  |   1  |
| 1 | 1 |  1  |  1  |   1  |

### 4-bit Adder
A 4-bit Adder is constructed by cascading four Full Adders. The carry output of each Full Adder is fed as the carry input to the next stage. It can add two 4-bit binary numbers, producing a 4-bit Sum and a final Carry-out.

---

## Observations

| Input A (4-bit) | Input B (4-bit) | Carry-in | Sum (4-bit) | Carry-out |
|-----------------|-----------------|----------|-------------|-----------|
| 0011  (3)       | 0101  (5)       |    0     | 1000  (8)   |     0     |
| 1010  (10)      | 0110  (6)       |    0     | 0000  (16)  |     1     |
| 1111  (15)      | 0001  (1)       |    0     | 0000  (16)  |     1     |
| 0111  (7)       | 0111  (7)       |    1     | 1111  (15)  |     0     |
| 1001  (9)       | 0011  (3)       |    0     | 1100  (12)  |     0     |

---

## Result

The Half Adder, Full Adder, and 4-bit Adder circuits were successfully designed and simulated on Logisim. The output values matched the expected truth table results, verifying the correctness of the designs.

---

## Conclusion

The experiment demonstrates how basic combinational logic circuits are built from simple gates. The Half Adder and Full Adder serve as fundamental building blocks for the 4-bit Adder, illustrating the concept of carry propagation in binary addition.