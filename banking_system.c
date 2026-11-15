#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "accounts.dat"
#define TEMP_FILE "accounts_temp.dat"

typedef struct {
    long accountNumber;
    char holderName[50];
    double balance;
} Account;

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

void readLine(const char *prompt, char *buffer, size_t size)
{
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) != NULL)
        buffer[strcspn(buffer, "\n")] = '\0';
}

int findAccount(long accountNumber, Account *result)
{
    FILE *fp = fopen(DATA_FILE, "rb");
    Account account;

    if (fp == NULL) return 0;

    while (fread(&account, sizeof(Account), 1, fp) == 1) {
        if (account.accountNumber == accountNumber) {
            if (result != NULL) *result = account;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void createAccount(void)
{
    FILE *fp;
    Account account;

    printf("\n--- Create Account ---\n");
    printf("Enter account number: ");
    if (scanf("%ld", &account.accountNumber) != 1 || account.accountNumber <= 0) {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (findAccount(account.accountNumber, NULL)) {
        printf("This account number already exists.\n");
        return;
    }

    readLine("Enter account holder name: ", account.holderName, sizeof(account.holderName));

    printf("Enter opening balance: ");
    if (scanf("%lf", &account.balance) != 1 || account.balance < 0) {
        printf("Invalid opening balance.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        perror("Unable to open account file");
        return;
    }

    if (fwrite(&account, sizeof(Account), 1, fp) == 1)
        printf("Account created successfully.\n");
    else
        printf("Error saving account.\n");

    fclose(fp);
}

void balanceEnquiry(void)
{
    long number;
    Account account;

    printf("Enter account number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (findAccount(number, &account)) {
        printf("\nAccount Number : %ld\n", account.accountNumber);
        printf("Account Holder : %s\n", account.holderName);
        printf("Available Balance: %.2f\n", account.balance);
    } else {
        printf("Account not found.\n");
    }
}

void updateBalance(long number, double amount, int isDeposit)
{
    FILE *fp = fopen(DATA_FILE, "r+b");
    Account account;
    int found = 0;

    if (fp == NULL) {
        printf("No account records found.\n");
        return;
    }

    while (fread(&account, sizeof(Account), 1, fp) == 1) {
        if (account.accountNumber == number) {
            if (!isDeposit && account.balance < amount) {
                printf("Insufficient balance. Transaction cancelled.\n");
                fclose(fp);
                return;
            }

            if (isDeposit)
                account.balance += amount;
            else
                account.balance -= amount;

            fseek(fp, -(long)sizeof(Account), SEEK_CUR);
            if (fwrite(&account, sizeof(Account), 1, fp) == 1) {
                printf("%s successful. Updated balance: %.2f\n",
                       isDeposit ? "Deposit" : "Withdrawal", account.balance);
            } else {
                printf("Could not save the transaction.\n");
            }
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) printf("Account not found.\n");
}

void depositMoney(void)
{
    long number;
    double amount;

    printf("Enter account number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter deposit amount: ");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("Amount must be greater than zero.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    updateBalance(number, amount, 1);
}

void withdrawMoney(void)
{
    long number;
    double amount;

    printf("Enter account number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter withdrawal amount: ");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("Amount must be greater than zero.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    updateBalance(number, amount, 0);
}

void listAccounts(void)
{
    FILE *fp = fopen(DATA_FILE, "rb");
    Account account;
    int count = 0;

    if (fp == NULL) {
        printf("No accounts available.\n");
        return;
    }

    printf("\n%-16s %-28s %-12s\n", "Account Number", "Holder Name", "Balance");
    printf("------------------------------------------------------------\n");

    while (fread(&account, sizeof(Account), 1, fp) == 1) {
        printf("%-16ld %-28s %-12.2f\n",
               account.accountNumber, account.holderName, account.balance);
        count++;
    }

    if (count == 0) printf("No accounts available.\n");
    fclose(fp);
}

int main(void)
{
    int choice;

    do {
        printf("\n====================================\n");
        printf("       BANK ACCOUNT MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid menu input. Exiting.\n");
            clearInputBuffer();
            break;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: balanceEnquiry(); break;
            case 5: listAccounts(); break;
            case 0: printf("Thank you for using the banking system.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
