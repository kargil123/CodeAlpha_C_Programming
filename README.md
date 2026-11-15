# Bank Account Management System (C)

## Objective
A console-based mini banking application supporting account creation, deposits, withdrawals, balance enquiry and account listing. Account data is saved in a binary file.

## Compile and run
```bash
gcc banking_system.c -o banking_system
./banking_system
```
Windows PowerShell:
```powershell
gcc banking_system.c -o banking_system.exe
.\banking_system.exe
```

## Features
- Create an account with a unique account number, holder name and opening balance.
- Deposit money into an existing account.
- Withdraw money while preventing overdrafts.
- Check an account's balance.
- Display all stored accounts.
- Persist account data in `accounts.dat`.

## Concepts used
Structures, functions, binary file handling, searching, loops, conditions, `switch-case` and arithmetic operations.

## Test checklist
1. Create an account with opening balance 1000.
2. Enquire the balance; it should show 1000.
3. Deposit 500; balance should become 1500.
4. Withdraw 200; balance should become 1300.
5. Attempt to withdraw 5000; transaction should be rejected.
6. Try an unknown account number.
7. Exit and restart; verify that the account remains stored.

## Important note
This is an educational console project, not real banking software. It does not implement authentication, encryption, audit logs, transaction rollback or production-grade financial controls. The binary data file is intended only for this demonstration.

## Explanation
An `Account` structure stores the account number, holder name and balance. Each menu operation is handled by a separate function. The application uses binary file operations to create, locate and update account records. Withdrawals are rejected if the requested amount exceeds the available balance.
