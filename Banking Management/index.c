#include <stdio.h>
#include <string.h>
#include <time.h>

void create_acc();
void deposit_money();
void withdraw_money();
void balance();
void transaction_history();       
void save_transaction(int acc_no, char type[], float amount, float after_balance);  


typedef struct
{
    char name[50];
    int acc_no;
    float balance;

} account;


// NEW: Transaction structure
typedef struct
{
    int acc_no;
    char type[20];       // "Deposit" or "Withdrawal"
    float amount;
    float balance_after;
    char date_time[30];  // stores date and time as string

} transaction;


int main() {
    int choice;
    do
    {
        printf("\n ------ Bank Management System ------ ");
        printf("\n 1. Create Account ");
        printf("\n 2. Deposit Money ");
        printf("\n 3. Withdraw Money");
        printf("\n 4. Check Balance ");
        printf("\n 5. Transaction History");   // NEW
        printf("\n 6. Exit");
        printf("\n Enter your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_acc();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            balance();
            break;
        case 5:
            transaction_history();    // NEW
            break;
        case 6:
            printf("\n======== Exiting Program ========\n Thank You for Visiting\n");
            break;

        default:
            printf("\n Invalid Choice");
            break;
        }

    } while (choice != 6);

    return 0;
}


// -----------------------------------------------------------------------
void create_acc() {
    account acc;

    FILE *file = fopen("account.dat", "ab+");
    if (file == NULL)
    {
        printf("Unable to open the File !!");
        return;
    }

    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("\n Enter Your Name : ");
    fgets(acc.name, sizeof(acc.name), stdin);

    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';

    printf("Enter Your Account Number : ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n Account Created Successfully \n ");
}


// -----------------------------------------------------------------------
void deposit_money() {
    int acc_number;
    float deposit;
    account acc_read;

    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Unable to open the File !!");
        return;
    }

    printf("\n Enter the Account Number : ");
    scanf("%d", &acc_number);

    printf("\nEnter the Amount to deposit : ");
    scanf("%f", &deposit);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_number)   // FIXED: was '=' now '=='
        {
            acc_read.balance += deposit;

            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);

            save_transaction(acc_number, "Deposit", deposit, acc_read.balance);  // NEW

            printf("\nSuccessfully Money is Deposited");
            printf("\n Deposit Amount   = Rs. %.2f \n", deposit);
            printf("\n Current Balance  = Rs. %.2f \n ", acc_read.balance);
            return;
        }
    }

    fclose(file);
    printf("\n Account number %d not found", acc_number);
}


// -----------------------------------------------------------------------
void withdraw_money() {
    int acc_number;
    float withdraw;
    account acc_read;

    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Unable to open the File !!");
        return;
    }

    printf("\n Enter Account Number : ");
    scanf("%d", &acc_number);

    printf("Enter the Withdrawal Amount : ");
    scanf("%f", &withdraw);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_number)
        {
            if (acc_read.balance >= withdraw)
            {
                acc_read.balance -= withdraw;
                fseek(file, -sizeof(acc_read), SEEK_CUR);
                fwrite(&acc_read, sizeof(acc_read), 1, file);

                save_transaction(acc_number, "Withdrawal", withdraw, acc_read.balance);  // NEW

                printf("\n Successfully withdrawn Rs. %.2f from Account \n", withdraw);
                printf("\n Remaining Balance   = Rs. %.2f \n ", acc_read.balance);
            }
            else
            {
                printf("\n Insufficient Balance");
            }
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n Account number %d not found \n ", acc_number);
}


// -----------------------------------------------------------------------
void balance() {
    int acc_number;
    account acc_read;

    FILE *file = fopen("account.dat", "rb");
    if (file == NULL)
    {
        printf("Unable to open the File !!");
        return;
    }

    printf("Enter Your Account Number : ");
    scanf("%d", &acc_number);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_number)
        {
            printf("\n Your Current Balance is Rs. %.2f \n ", acc_read.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\n Account number %d not Found !! \n ", acc_number);
}


// -----------------------------------------------------------------------
// NEW: Save a transaction record to transactions.dat
void save_transaction(int acc_no, char type[], float amount, float after_balance) {
    transaction t;

    t.acc_no = acc_no;
    strcpy(t.type, type);
    t.amount = amount;
    t.balance_after = after_balance;

    // Get current date and time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(t.date_time, sizeof(t.date_time), "%d-%m-%Y %H:%M:%S", tm_info);

    FILE *file = fopen("transactions.dat", "ab");
    if (file == NULL)
    {
        printf("\n Warning: Could not save transaction record.");
        return;
    }

    fwrite(&t, sizeof(t), 1, file);
    fclose(file);
}


// -----------------------------------------------------------------------
// NEW: Display all transactions for a given account number
void transaction_history() {
    int acc_number;
    transaction t;
    int found = 0;

    printf("\n Enter Account Number : ");
    scanf("%d", &acc_number);

    FILE *file = fopen("transactions.dat", "rb");
    if (file == NULL)
    {
        printf("\n No transactions found. File does not exist yet.");
        return;
    }

    printf("\n ============================================");
    printf("\n      Transaction History - Acc No: %d", acc_number);
    printf("\n ============================================");
    printf("\n %-12s %-12s %-12s %-20s", "Type", "Amount", "Balance", "Date & Time");
    printf("\n --------------------------------------------");

    while (fread(&t, sizeof(t), 1, file))
    {
        if (t.acc_no == acc_number)
        {
            printf("\n %-12s Rs.%-9.2f Rs.%-9.2f %s",
                   t.type, t.amount, t.balance_after, t.date_time);
            found++;
        }
    }

    fclose(file);

    if (found == 0)
        printf("\n No transactions found for Account %d.", acc_number);
    else
        printf("\n --------------------------------------------");
        printf("\n Total Transactions : %d \n ", found);
}