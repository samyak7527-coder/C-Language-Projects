
#include <stdio.h>

// importing library for the random number generation :
#include <stdlib.h>
#include <time.h>

int main()
{
    int random, guess, no_guess = 0;

    /*rand() → gives numbers
    srand(seed) → decides starting point
    time(NULL) → gives changing seed*/

    srand(time(NULL)); // Seeding the random number;

    printf("Welcome to the Number Guessing Game\n");
    random = (rand() % 100) + 1;

    // We use do-while loop because we want atleast 1 guess from the user ;
    do
    {
        printf("Enter the number between (1 to 100) : ");
        scanf("%d", &guess);
        no_guess++;

        if (guess < random)
        {
            printf("Guess larger number \n");
        }
        else if (guess > random)
        {
            printf("Guess smaller number \n");
        }
        else
        {
            printf("You have successfully guessed the number in %d attempts\n", no_guess);
        }

    } while (guess != random);

    printf("Thanks for playing the game\n");
    printf("\n \t\t Developed by: Samyak\n");

    return 0;
}