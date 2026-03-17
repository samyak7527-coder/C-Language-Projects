
#include <stdio.h> 
# include <math.h>

int main() {
    int choice ; 
    float  a ,b , sum , sub , div , mul , Pow;
    printf("\nEnter the 1st number : ");
    scanf("%f",&a);
    printf("\n Enter the 2nd Choice : ");
    scanf("%f",&b);
    do
    {
        printf("-----------------------------");
        printf("\nSelect your Choice : ");
        printf("\n 1. Addition \n 2.Substraction \n 3. Division \n 4. Multiplication \n 5. Power \n 6. Exit");
        printf("\n Enter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            // Addition : 
            sum = a + b ;
            printf("\nThe Sum is =%.2f ",sum);

            break;
        case 2 : 
            
            sub = a-b ; 
            printf("\nThe Diffrence is = %.2f",sub);
            break;
        
        case 3 : 
            
            div = a/b ;
            printf("The Division is = %.2f",div);
            
            break;
        
        case 4 : 

            mul = a * b ; 
            printf("The Multiplication is = %.2f ",mul);


            break;
        
        case 5 : 

            Pow = pow(a,b);
            printf("The Power is = %.2f",Pow);

            break;

        case 6 : 
            printf("------ Existing Program ------");
            break;
        
        default:
            printf("\n Invalid Choice : ");
            break;
        }
    } while (choice!=6);
    

    return 0 ; 
}