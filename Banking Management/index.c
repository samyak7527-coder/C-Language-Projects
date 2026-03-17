#include <stdio.h> 
# include <string.h>


void create_acc();
void deposit_money();
void withdraw_money();
void balance();



typedef struct 
{
    char name[50];
    int acc_no ; 
    float balance ; 

} account ;


int main() {
    int choice ; 
    do
    {
        printf("\n ------ Bank Management Store ------ ");
        printf("\n 1. Create Account ");
        printf("\n 2. Deposit Money ");
        printf("\n 3. Withdraw Money");
        printf("\n 4. Check Balance ");
        printf("\n 5. Exit");
        printf("\n Enter your Choice : ");
        scanf("%d",&choice); 

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
        printf("\n======== Exiting Program======== \n Thank You for Visiting");
        
        break;
    
    default:
    printf("\n Invalid Choice");
        break;
    }

    } while (choice!=5);

    return 0 ; 
}

void create_acc(){
    account acc ; // acc as a variable of the structure account

    FILE *file = fopen("account.dat","ab+");  // .dat is used for the binary file and .txt for the simple text file
    // Open the file in the append binary mode ; 
    if (file==NULL)
    {
        printf("Unable to open the File !!");
        return ; 
    }

    char c ; 
    do
    {
        c = getchar();
    } while (c != '\n' && c!=EOF);
    

    printf("\n Enter Your Name : ");
    fgets(acc.name , sizeof(acc.name) , stdin);

    // Fixing the problem of the fgets
    int ind = strcspn(acc.name , "\n");   
    acc.name[ind] = '\0';

    printf("Enter Your Account Number : ");
    scanf("%d",&acc.acc_no);
    acc.balance = 0 ; 

    fwrite(&acc , sizeof(acc),1 , file);
    // fwrite(what you want to write , size of that address , no. of variables , file_name or the file pointer );

    fclose(file);
    printf("\n Account Created Successfully");

}
// ---------------------------------------------------------------------------------------------------------------------------------------

void deposit_money(){
    int acc_number ; 
    float deposit ; 
    account acc_read ;
    FILE *file = fopen("account.dat","rb+");
    if (file==NULL)
    {
        printf("Unable to open the File !!");
        return ; 
    } 

    printf("\n Enter the Account Number : ");
    scanf("%d",&acc_number);

    printf("\nEnter the Amount to deposit : ");
    scanf("%f",&deposit);

    while (fread(&acc_read , sizeof(acc_read),1,file))
    {
        if (acc_read.acc_no = acc_number)
        {
            acc_read.balance+=deposit ; 
            
            fseek(file , -sizeof(acc_read) , SEEK_CUR);  
            // fseek (pointer , where to overwrite  , cursor postion)
            //  '-'  == move the cursor to staring postion of the content size.
            // We are here overwritng the content of the file and moving the cursor to the staring postion using fseek
            
            fwrite(&acc_read , sizeof(acc_read),1 , file);
            fclose(file);
            
            printf("\nSuccessfully Money is Deposited");
            printf("\n Deposit Amount = %.2f",deposit);
            printf("\n Your Current balance is %.2f",acc_read.balance);
            return ; 
        }
        
    }

    fclose(file);
    printf("\n Account number %d not found",acc_number);
    


}

//---------------------------------------------------------------------------------------------------------------------------------------------

void withdraw_money(){
    int acc_number; 
    float withdraw ; 
    account acc_read ; 

    FILE *file = fopen("account.dat","rb+");
    if (file==NULL)
    {
        printf("Unable to open the File !!");
        return ; 
    }

    printf("\n Enter Account Number : ");
    scanf("%d",&acc_number);

    printf("Enter the Withdrawal Amount :");
    scanf("%f",&withdraw);

    while (fread(&acc_read , sizeof(acc_read),1 , file))        
    {
        if (acc_read.acc_no  == acc_number) 
        {
            if (acc_read.balance >= withdraw)
            {
                acc_read.balance-=withdraw ; 
                fseek(file , -sizeof(acc_read) , SEEK_CUR);
                fwrite(&acc_read , sizeof(acc_read),1,file);
                printf("\n Successfully withdrawn %.2f from Account",withdraw);
                printf("\n Remaining balance is Rs. %.2f",acc_read.balance);
                

            }
            else{
                printf("\n Insufficient Balance") ; 
            }
            fclose(file);
            return ; 
            
        }

        fclose(file);
        printf("\n Account number %d not found",acc_number);
        
    }
    


}
// -----------------------------------------------------------------------------------------------------------------------------------------------
void balance(){
    int acc_number ;
    account acc_read ; 
    FILE *file = fopen("account.dat","rb");

    if (file==NULL)
    {
        printf("Unable to open the File !!");
        return ; 
    }
    printf("Enter Your Account Number : ");
    scanf("%d",&acc_number);

    while (fread(&acc_read , sizeof(acc_read),1 , file))
    {
        if (acc_read.acc_no == acc_number)
        {
            printf("\n Your Current Balance is Rs. %.2f",acc_read.balance);
            fclose(file);
            return ;
        }
        
    }
    fclose(file);
    printf("\n Account number %d not Found !!",acc_number);
    
}

