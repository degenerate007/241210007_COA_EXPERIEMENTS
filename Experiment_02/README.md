# Experiment 2

**Date:** 02-02-2026

---

## AIM

To design and verify an 8×1 Multiplexer (MUX) and an 8×3 Encoder using basic logic gates on Logisim.

---

## Software Used

- **Logisim** — A graphical tool for designing and simulating digital logic circuits.

---

## Theory

### 8×1 Multiplexer (MUX)
A Multiplexer is a combinational circuit that selects one of many input lines and directs it to a single output line. An 8×1 MUX has:
- **8 data inputs:** D0 to D7
- **3 select lines:** S0, S1, S2
- **1 output:** Y

The output expression is:
```
Y = D0·S2'S1'S0' + D1·S2'S1'S0 + D2·S2'S1S0' + D3·S2'S1S0
  + D4·S2S1'S0' + D5·S2S1'S0 + D6·S2S1S0' + D7·S2S1S0
```

| S2 | S1 | S0 | Output (Y) |
|----|----|----|------------|
|  0 |  0 |  0 |     D0     |
|  0 |  0 |  1 |     D1     |
|  0 |  1 |  0 |     D2     |
|  0 |  1 |  1 |     D3     |
|  1 |  0 |  0 |     D4     |
|  1 |  0 |  1 |     D5     |
|  1 |  1 |  0 |     D6     |
|  1 |  1 |  1 |     D7     |

### 8×3 Encoder
An Encoder is a combinational circuit that converts 2ⁿ input lines into n output lines. An 8×3 (Octal-to-Binary) Encoder has:
- **8 input lines:** I0 to I7 (only one active at a time)
- **3 output lines:** A2, A1, A0

Output expressions:
```
A2 = I4 + I5 + I6 + I7
A1 = I2 + I3 + I6 + I7
A0 = I1 + I3 + I5 + I7
```

| Active Input | A2 | A1 | A0 |
|--------------|----|----|----|
| I0           |  0 |  0 |  0 |
| I1           |  0 |  0 |  1 |
| I2           |  0 |  1 |  0 |
| I3           |  0 |  1 |  1 |
| I4           |  1 |  0 |  0 |
| I5           |  1 |  0 |  1 |
| I6           |  1 |  1 |  0 |
| I7           |  1 |  1 |  1 |

---

## Observations

### 8×1 MUX

| S2 | S1 | S0 | Input Selected | Observed Output (Y) |
|----|----|----|----------------|----------------------|
|  0 |  0 |  0 |      D0 = 1    |          1           |
|  0 |  0 |  1 |      D1 = 0    |          0           |
|  0 |  1 |  0 |      D2 = 1    |          1           |
|  0 |  1 |  1 |      D3 = 1    |          1           |
|  1 |  0 |  0 |      D4 = 0    |          0           |
|  1 |  0 |  1 |      D5 = 1    |          1           |
|  1 |  1 |  0 |      D6 = 0    |          0           |
|  1 |  1 |  1 |      D7 = 1    |          1           |

### 8×3 Encoder

| Active Input | Observed A2 | Observed A1 | Observed A0 |
|--------------|-------------|-------------|-------------|
|      I0      |      0      |      0      |      0      |
|      I1      |      0      |      0      |      1      |
|      I2      |      0      |      1      |      0      |
|      I3      |      0      |      1      |      1      |
|      I4      |      1      |      0      |      0      |
|      I5      |      1      |      0      |      1      |
|      I6      |      1      |      1      |      0      |
|      I7      |      1      |      1      |      1      |

---

## Result

The 8×1 Multiplexer and 8×3 Encoder circuits were successfully designed using basic logic gates in Logisim and verified against the expected truth tables.

---

## Conclusion

This experiment illustrates data selection and encoding operations in digital systems. The MUX demonstrates how a single output line can represent multiple data inputs based on select lines, while the encoder compresses 8 input lines into a compact 3-bit binary code.