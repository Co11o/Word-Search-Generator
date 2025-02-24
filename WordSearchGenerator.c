//Jackson Collalti
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

char Grid[20][20];
bool InsertDownwards(int i, int WordLength, char *argv[], int GridSize);
bool InsertRightwards(int i, int WordLength, char *argv[], int GridSize);
bool InsertDiagonalDown(int i, int WordLength, char *argv[], int GridSize);
bool InsertDiagonalUp(int i, int WordLength, char *argv[], int GridSize);

int main(int argc, char *argv[])
{
    /*
        NOTE:  argv[1] = GridSize (int)
               argv[2] and up are words. *Words are intended to be typed in lower case
                                          upper case is allowed, and makes search easier to find
                                          since random characters in the grid are generated as
                                          lower case.

    */
    int i, j, l;
    int GridSize;
    srand(time(NULL));
    int Direction; // 0=diagonal up (Up and to the Right), 1=rightward, 2=diagonal down (Down and to the Right), and 3=downward.
    int WordLength;

    // Square Size
    GridSize = atoi(argv[1]);

    // Create Empty Grid
    for (i = 0; i < GridSize; i++)
    {
        for (j = 0; j < GridSize; j++)
        {
            Grid[i][j] = '-';
        }
    }

    Direction = 0;

    printf("Word List:\n");
    // Words
    for (i = 2; i < argc; i++)
    {
        // Get Word Length and Print word list
        WordLength = 0;
        //printf("Word %d: ", (i - 1));
        for (j = 0; argv[i][j] != '\0'; j++)
        {
            printf("%c", argv[i][j]);
            WordLength++;
        }
        printf("\n");

        // If word length is greater than grid can allow print word and terminate program
        if (WordLength > GridSize)
        {
            printf("Input ");
            for (j = 0; argv[i][j] != '\0'; j++)
            {
                printf("%c", argv[i][j]);
            }
            printf(": Can't be mapped");
            break;
        }

        // Random direction
        Direction = rand() % 4;
        l = 0;

        // Test If Insertable
        // 0=diagonal up (Up and to the Right), 1=rightward, 2=diagonal down (Down and to the Right), and 3=downward.
        while (l < 4)
        {
            if (Direction == 0)
            {
                // Failed to map
                if (!InsertDiagonalUp(i, WordLength, argv, GridSize))
                {
                    Direction++;
                }
                else
                {
                    break;
                }
            }
            else if (Direction == 1)
            {
                if (!InsertRightwards(i, WordLength, argv, GridSize))
                {
                    Direction++;
                }
                else
                {
                    break;
                }
            }
            else if (Direction == 2)
            {
                if (!InsertDiagonalDown(i, WordLength, argv, GridSize))
                {
                    Direction++;
                }
                else
                {
                    break;
                }
            }
            else if (Direction == 3)
            {
                if (!InsertDownwards(i, WordLength, argv, GridSize))
                {
                    Direction = 0;
                }
                else
                {
                    break;
                }
            }
            if (l == 3)
            {
                printf("Input ");
                for (j = 0; argv[i][j] != '\0'; j++)
                {
                    printf("%c", argv[i][j]);
                }
                printf(": Can't be mapped");
                break;
            }
            l++;
        }
    }
    printf("\n");

    // Fill "Empty" Slots
    for (i = 0; i < GridSize; i++)
    {
        for (j = 0; j < GridSize; j++)
        {
            // If not part of word, then Random char
            // In this implementation all random chars
            // will be lower case a-z
            if ((Grid[i][j]) == '-')
            {
                Grid[i][j] = 'a' + (rand() % 26);
            }
        }
    }

    // Print Grid
    for (i = 0; i < GridSize; i++)
    {
        for (j = 0; j < GridSize; j++)
        {
            if (j == (GridSize - 1))
            {
                printf("%c", Grid[i][j]);
            }
            else
            {
                printf("%c ", Grid[i][j]);
            }
        }
        printf("\n");
    }
}

/*
Example
- - c - -
- - a - -
- - t - -
*/
bool InsertDownwards(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = rand() % GridSize;                      // Random X coordinate for first char of word
    int WordStartingYIndex = (rand() % (GridSize - WordLength + 1)); // Random Y coordinate for first char of word
                                                                     //  Y coordinate must be at (GridSize - WordLength + 1)
                                                                     //  To fit in grid
    int l, k;
    bool canInsert;
    l = 0;

    // While a valid location is still possible
    while (l < (GridSize * (GridSize - WordLength + 1)))
    {
        canInsert = true;
        // Checks if word can be inserted
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex + k][WordStartingXIndex] != '-')
            {
                if (Grid[WordStartingYIndex + k][WordStartingXIndex] == argv[i][k])
                {
                    continue;
                }
                else
                {
                    canInsert = false;
                    break;
                }
            }
        }
        // If word can be inserted then fill in grid with word
        if (canInsert)
        {
            for (k = 0; k < WordLength; k++)
            {
                Grid[WordStartingYIndex + k][WordStartingXIndex] = argv[i][k];
            }
            break;
        }
        // Iterate through Y coords
        else if (l == (GridSize - WordLength + 1))
        {
            WordStartingYIndex = WordStartingYIndex - 1;
        }
        // Iterate through X coords
        else
        {
            WordStartingXIndex = (WordStartingXIndex + 1) % GridSize;
        }
        l++;
    }
    if (canInsert)
    {
        //printf(" Downward: Starts at (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
        return true; // Word can and has been inserted into grid
    }
    else
    {
        return false; // Word can't be inserted anywhere
    }
}

/*
Example
- - c a t
- - - - -
- - - - -
*/
bool InsertRightwards(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = (rand() % (GridSize - WordLength + 1));
    int WordStartingYIndex = rand() % GridSize;
    int l, k;
    bool canInsert;
    l = 0;
    while (l < (GridSize * (GridSize - WordLength + 1)))
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex][WordStartingXIndex + k] != '-')
            {
                if (Grid[WordStartingYIndex][WordStartingXIndex + k] == argv[i][k])
                {
                    continue;
                }
                else
                {
                    canInsert = false;
                    break;
                }
            }
        }
        if (canInsert)
        {
            for (k = 0; k < WordLength; k++)
            {
                Grid[WordStartingYIndex][WordStartingXIndex + k] = argv[i][k];
            }
            break;
        }
        else if (l == (GridSize - WordLength + 1))
        {
            WordStartingXIndex = WordStartingXIndex - 1;
        }
        else
        {
            WordStartingYIndex = (WordStartingYIndex + 1) % GridSize;
        }
        l++;
    }
    if (canInsert)
    {
        //printf(" Rightward: Starts at (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
        return true;
    }
    else
    {
        return false;
    }
}

/*
Example
- - C - -
- - - A -
- - - - T
*/
bool InsertDiagonalDown(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = (rand() % (GridSize - WordLength + 1));
    int WordStartingYIndex = (rand() % (GridSize - WordLength + 1));
    int l, k;
    bool canInsert;
    l = 0;
    while (l < ((GridSize - WordLength + 1) * (GridSize - WordLength + 1)))
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex + k][WordStartingXIndex + k] != '-')
            {
                if (Grid[WordStartingYIndex + k][WordStartingXIndex + k] == argv[i][k])
                {
                    continue;
                }
                else
                {
                    canInsert = false;
                    break;
                }
            }
        }
        if (canInsert)
        {
            for (k = 0; k < WordLength; k++)
            {
                Grid[WordStartingYIndex + k][WordStartingXIndex + k] = argv[i][k];
            }
            break;
        }
        else if (l == (GridSize - WordLength + 1))
        {
            WordStartingYIndex = (WordStartingYIndex + 1) % (GridSize - WordLength + 1);
        }
        else
        {
            WordStartingXIndex = (WordStartingXIndex + 1) % (GridSize - WordLength + 1);
        }
        l++;
    }
    if (canInsert)
    {
        //printf(" Diagonal Down: Starts at (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
        return true;
    }
    else
    {
        return false;
    }
}

/*
Example
- - - - t
- - - a -
- - c - -
*/
bool InsertDiagonalUp(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = (rand() % (GridSize - WordLength + 1));
    int WordStartingYIndex = GridSize - 1 - (rand() % (GridSize - WordLength + 1));
    int l, k;
    bool canInsert;
    l = 0;
    while (l < ((GridSize - WordLength + 1) * (GridSize - WordLength + 1)))
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex - k][WordStartingXIndex + k] != '-')
            {
                if (Grid[WordStartingYIndex - k][WordStartingXIndex + k] == argv[i][k])
                {
                    continue;
                }
                else
                {
                    canInsert = false;
                    break;
                }
            }
        }
        if (canInsert)
        {
            for (k = 0; k < WordLength; k++)
            {
                Grid[WordStartingYIndex - k][WordStartingXIndex + k] = argv[i][k];
            }
            break;
        }
        else if (l == (GridSize - WordLength + 1))
        {
            WordStartingYIndex = GridSize - 1 - (WordStartingYIndex + 1) % (GridSize - WordLength + 1);
        }
        else
        {
            WordStartingXIndex = (WordStartingXIndex + 1) % (GridSize - WordLength + 1);
        }
        l++;
    }
    if (canInsert)
    {
        //printf(" Diagonal Up: Starts at (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
        return true;
    }
    else
    {
        return false;
    }
}