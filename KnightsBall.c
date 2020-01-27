// Ayberk Aydin
// COP 3502C
// Section 0004
// Program 1 (aka “Wake-Up Call”) UCF KnightsBall Lottery
// 01/25/2019

#include <stdio.h>
#include <stdlib.h>

// Enumerated type for the four possible winning values
enum winners_prizes {prize1 = 10, prize2 = 100, prize3 = 10000, prize4 = 1000000};

// Struct given from the assignment description
typedef struct KnightsBallLottoPlayer {
    char firstName[20];
    char lastName[20];
    int numbers[6];
} KBLottoPlayer;

// Binary search function prototype
int BinarySearch(int [], int, int, int);

int main()
{
    // Declaration of input file pointer
    FILE * fin;

    // If-statement to ensure that file is found before executing the rest of the code
    if ((fin = fopen("KnightsBall.in", "r")) == NULL)
    {
        printf("Could not find file.");
        return 0;
    }

    // Scanning the first line of input file for n (number of tickets purchased/players)
    int num_of_players;
    fscanf(fin, "%d", &num_of_players);

    // Declaring the array of structs where each struct represents a single lottery player
    // This is done using a pointer to the data-type KBLottoPlayer defined above as was shown with the data-type int in class
    KBLottoPlayer * lotto_players_arr;

    // Dynamic memory allocation for the array of lottery players
    // If-statement to ensure that enough memory is available for the array
    // Similar to fopen, malloc returns a NULL pointer when memory cannot be allocated
    if ((lotto_players_arr = (KBLottoPlayer *) malloc(sizeof(KBLottoPlayer) * num_of_players)) == NULL)
    {
        printf("Could not allocate memory.");
        return 0;
    }

    // Declaration of counters for upcoming nested for-loops
    int i, j;

    // Nested for-loop for inputting data from KnightsBall.in into array of structs
    for (i=0; i<num_of_players; i++)
    {
        // Inputting players' first and last name into array
        fscanf(fin, "%s %s", lotto_players_arr[i].lastName, lotto_players_arr[i].firstName);

        // Inputting players' chosen numbers into array
        for (j=0; j<6; j++)
        {
            fscanf(fin, "%d", &lotto_players_arr[i].numbers[j]);
        }
    }

    // Done with inputting from this file, so close it
    fclose(fin);

    // Now open KnightsBall.out to output the winners of the lottery
    // Again, make sure the file opens before proceeding by using an if-statement
    FILE * fout;
    if ((fout = fopen("KnightsBall.out", "w")) == NULL)
    {
        printf("Could not open file.");
        return 0;
    }

    // Declaration of user-inputted array of winning lottery numbers
    int winning_nums[6];

    // Asking user to input these numbers into above array
    printf("Enter the winning Lottery numbers:\n");
    for (i=0; i<6; i++)
    {
        scanf("%d", &winning_nums[i]);
    }

    // Declaration of a counter to keep track of an individual's number of matches to the winning numbers
    // Winnings variable to determine the dollar amount paid to said individual
    int counter, winnings;

    // Outer for-loop switches between each player
    for (i=0; i<num_of_players; i++)
    {
        // Counter Initialization
        counter = 0;

        // Inner for-loop sends each player's chosen numbers and one winning number at a time to determine a match
        for (j=0; j<6; j++)
        {
            // If the binary search returns 1, the winning number matches one of the player's numbers
            if ((BinarySearch(lotto_players_arr[i].numbers, 0, 5, winning_nums[j])) == 1)
                {
                    // Increments player's counter each time a match is made
                    counter++;
                }
        }

        // If a player has at least 3 matches, he wins some money and so his name should be listed in the output file
        if (counter >= 3)
        {
            // Switch-statement to determine the exact winnings of this player, which is the dependent on the counter
            // The enumerated type is implemented here as well
            switch (counter) {
                case 3:
                    winnings = prize1;
                    break;
                case 4:
                    winnings = prize2;
                    break;
                case 5:
                    winnings = prize3;
                    break;

                // The default case wins the most money
                default:
                    winnings = prize4;
            }

            // Now we print to KnightsBall.out this winning individual's data
            fprintf(fout, "%s %s matched %d numbers and won $%d.\n", lotto_players_arr[i].firstName, lotto_players_arr[i].lastName, counter, winnings);
        }
    }

    // Finally we close the output file once outputting is finished
    fclose(fout);

    return 0;
}

// Binary search function to determine all the players' matches to the winning numbers
int BinarySearch(int arr[], int low, int high, int value)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // Check to see if value is at the index mid
        if (arr[mid] == value)
            return 1;

        // If value is greater, we ignore the left half of the array
        if (arr[mid] < value)
            low = mid + 1;

        // If value is smaller, we ignore the right half of the array
        else
            high = mid - 1;
    }

    // Could not find value in given array
    return 0;
}
