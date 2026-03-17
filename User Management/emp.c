#include <stdio.h> 
# include <string.h>

# define MAX_USERS 10  // I can have only maximum 10 users
# define CREDENTIAL_LENGTH 30

typedef struct 
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
}user;

user users[MAX_USERS];

int user_count = 0 ;  // Counting the users ;

void register_user();
int login_user() ; // returns the user index ; 
void fix_gets_input(char*);
void input_credential(char*username , char *password);

int main() {
    int option , user_index; 
    while (1)
    {
    printf("\n \n Welcome to User Management");
    printf("\n 1. Register");
    printf("\n 2. Login");
    printf("\n 3. Exit");
    printf("\n Select an option : ");
    scanf("%d",&option);
    getchar();  // consume extra Enter


    switch (option)
    {
    case 1:
        register_user();
        break;
    case 2:
        user_index = login_user();
        if (user_index>=0)
        {
            printf("\n Login Successfull . Welcome %s" , users[user_index].username);
        }
        else{
            printf("\n Login Failed . Incorrect Username or Password");
        }
        
        break;
    case 3:
        printf("\n --- Exiting Program ---");
        return 0 ;
        break;
    
    default:
        printf("\n --- Invalid Option Choose . Please Try Again -----");
        break;
    }
    }

    return 0 ; 
}

void register_user() {
    if (user_count == MAX_USERS)
    {
        printf("\n Maximum %d users are supported ! No more registrations Allowed !!!!",MAX_USERS);
        return ; 
    }
    int new_index = user_count ; 
    printf("\nRegistration of new user");
    input_credential(users[new_index].username ,users[new_index].password) ;
    user_count++;
    printf("Registration Successfull! \n");
}

int login_user(){
    char username[CREDENTIAL_LENGTH], password[CREDENTIAL_LENGTH];
    input_credential(username , password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username , users[i].username)==0 && strcmp(password , users[i].password)==0)
        {
            return i ; 
        }
        
    }
    return -1 ;
}

void  fix_gets_input(char* string){
    int index = strcspn(string , "\n");  // Finds the index of the "\n"
    string[index] = "\0";
}

void input_credential(char *username,char* password){
    printf("\n Enter Username : ");
    fgets(username , CREDENTIAL_LENGTH , stdin);
    fix_gets_input(username);
    
    printf("Enter Password : ") ;
    fgets(password,CREDENTIAL_LENGTH , stdin);
    fix_gets_input(password);
}