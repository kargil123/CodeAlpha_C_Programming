# Matrix Operations (C)

## Objective
Implement matrix addition, matrix multiplication and transpose using functions and two-dimensional arrays.

## Compile and run
```bash
gcc matrix.c -o matrix
./matrix
```
Windows PowerShell:
```powershell
gcc matrix.c -o matrix.exe
.\matrix.exe
```

## Features
- Accepts matrices up to 10 x 10.
- Adds matrices when their dimensions match.
- Multiplies matrices when columns of A equal rows of B.
- Calculates transpose for either matrix.
- Displays the entered matrices through a menu.

## Concepts used
2D arrays, functions, nested loops, conditions, `switch-case` and matrix arithmetic.

## Suggested test
Matrix A (2 x 2): `1 2 / 3 4`
Matrix B (2 x 2): `5 6 / 7 8`

Expected A + B:
```text
6  8
10 12
```
Expected A x B:
```text
19 22
43 50
```
Expected transpose of A:
```text
1 3
2 4
```

## Explanation
The program reads the dimensions and elements of two matrices. Separate functions perform addition, multiplication, transpose and display. Before addition or multiplication, the program checks the dimension rules to avoid invalid operations.
