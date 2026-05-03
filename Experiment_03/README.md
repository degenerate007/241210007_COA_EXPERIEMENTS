# Experiment 3

**Date:** 09-02-2026

---

## AIM

To design and verify a 4-bit Ripple Carry Adder (RCA) and to study the propagation delay on Logisim.

---

## Software Used

- **Logisim** — A graphical tool for designing and simulating digital logic circuits, including built-in support for timing/propagation delay analysis.

---

## Theory

### 4-bit Ripple Carry Adder (RCA)
A Ripple Carry Adder is formed by cascading multiple Full Adders in series. In a 4-bit RCA:
- Four Full Adders are connected such that the **Carry-out** of one stage feeds the **Carry-in** of the next stage.
- The inputs are two 4-bit numbers: **A = A3A2A1A0** and **B = B3B2B1B0**
- The output is a 4-bit **Sum = S3S2S1S0** and a **Carry-out (C4)**

### Propagation Delay
Propagation delay is the time taken for a change in input to produce a stable output. In a Ripple Carry Adder, the carry signal must "ripple" through all stages sequentially:

- If each Full Adder has a carry propagation delay of **t**,
- Then the total propagation delay of an n-bit RCA = **n × t**

For a 4-bit RCA:
```
Total Delay = 4 × (delay of one Full Adder)
```

This is the primary limitation of RCAs — the delay grows linearly with the number of bits, making them slow for wide adders. This limitation is overcome by **Carry Lookahead Adders (CLA)**.

### Truth Table (Sample Cases)

| A (4-bit) | B (4-bit) | Cin | Sum (4-bit) | Cout |
|-----------|-----------|-----|-------------|------|
| 0011 (3)  | 0101 (5)  |  0  | 1000  (8)   |  0   |
| 1111 (15) | 0001 (1)  |  0  | 0000  (0)   |  1   |
| 1010 (10) | 0110 (6)  |  0  | 0000  (16)  |  1   |

---

## Observations

### Circuit Output Verification

| A (4-bit) | B (4-bit) | Cin | Expected Sum | Observed Sum | Expected Cout | Observed Cout |
|-----------|-----------|-----|--------------|--------------|---------------|---------------|
| 0011 (3)  | 0101 (5)  |  0  |  1000  (8)   |  1000  (8)   |       0       |       0       |
| 1111 (15) | 0001 (1)  |  0  |  0000  (16)  |  0000  (16)  |       1       |       1       |
| 0110 (6)  | 0011 (3)  |  1  |  1010  (10)  |  1010  (10)  |       0       |       0       |
| 1010 (10) | 0110 (6)  |  0  |  0000  (16)  |  0000  (16)  |       1       |       1       |
| 0100 (4)  | 0100 (4)  |  0  |  1000  (8)   |  1000  (8)   |       0       |       0       |

### Propagation Delay Observation

| Stage | Component  | Propagation Delay (ns / simulation units) |
|-------|------------|-------------------------------------------|
|   1   | Full Adder |                20 ns                      |
|   2   | Full Adder |                20 ns                      |
|   3   | Full Adder |                20 ns                      |
|   4   | Full Adder |                20 ns                      |
| Total | 4-bit RCA  |                80 ns                      |

---

## Result

The 4-bit Ripple Carry Adder was successfully designed and verified on Logisim. The propagation delay was observed to increase with each cascaded Full Adder stage, confirming the ripple effect of carry propagation.

---

## Conclusion

The experiment demonstrates the working of a Ripple Carry Adder and highlights the issue of increasing propagation delay in multi-bit adders. The delay analysis confirms that RCAs, while simple to design, become inefficient for large bit-widths due to sequential carry propagation.