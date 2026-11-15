# Basic Calculator (C)

## Objective
Create a console-based calculator that performs addition, subtraction, multiplication and division using a `switch` statement.

## Requirements
- GCC compiler
- VS Code or any C IDE

## Compile and run
```bash
gcc calculator.c -o calculator
./calculator
```
On Windows:
```powershell
gcc calculator.c -o calculator.exe
.\calculator.exe
```

## Concepts used
Variables, `double`, formatted input/output, `switch-case`, conditional statements and arithmetic operators.

## Test cases
| First number | Operator | Second number | Expected result |
|---:|:---:|---:|---|
| 12 | + | 8 | 20.00 |
| 12.5 | - | 2.5 | 10.00 |
| 4 | * | 3 | 12.00 |
| 10 | / | 2 | 5.00 |
| 10 | / | 0 | Division-by-zero error |
| 5 | % | 2 | Invalid operator |

## Explanation
The program reads two numbers and an arithmetic operator. A `switch` statement selects the requested operation. Division checks whether the second number is zero before calculating the result.
