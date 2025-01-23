#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

char Grid[20][20];
void InsertDownwards(int i, int WordLength, char *argv[], int GridSize);
void InsertRightwards(int i, int WordLength, char *argv[], int GridSize);
void InsertDiagonalDown(int i, int WordLength, char *argv[], int GridSize);
void InsertDiagonalUp(int i, int WordLength, char *argv[], int GridSize);

int main(int argc, char *argv[])
{
    int i, j;
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

    // Print Empty Grid
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

    Direction = 0;

    // Words
    for (i = 2; i < argc; i++)
    {
        // Get Word Length
        WordLength = 0;
        printf("Word %d: ", (i - 1));
        for (j = 0; argv[i][j] != '\0'; j++)
        {
            printf("%c", argv[i][j]);
            WordLength++;
        }
        printf(" %d ", WordLength);

        Direction = rand() % 4;

        // Test If Insertable
        // 0=diagonal up (Up and to the Right), 1=rightward, 2=diagonal down (Down and to the Right), and 3=downward.
        if (Direction == 0)
        {
            InsertDiagonalUp(i, WordLength, argv, GridSize);
        }
        if (Direction == 1)
        {
            InsertRightwards(i, WordLength, argv, GridSize);
        }
        if (Direction == 2)
        {
            InsertDiagonalDown(i, WordLength, argv, GridSize);
        }
        if (Direction == 3)
        {
            InsertDownwards(i, WordLength, argv, GridSize);
        }
    }
    printf("\n");

    // Fill Empty Slots
    
        for (i = 0; i < GridSize; i++)
        {
            for (j = 0; j < GridSize; j++)
            {
                // If not part of word, then Random char
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

void InsertDownwards(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = rand() % GridSize;
    int WordStartingYIndex = (rand() % (GridSize - WordLength + 1));
    int l, k;
    bool canInsert;
    l = 0;
    while (l < 10)
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex + k][WordStartingXIndex] != '-')
            {
                canInsert = false;
                break;
            }
        }
        if (canInsert)
        {
            for (k = 0; k < WordLength; k++)
            {
                Grid[WordStartingYIndex + k][WordStartingXIndex] = argv[i][k];
            }
            break;
        }
        else if (l == 5)
        {
            WordStartingYIndex = WordStartingYIndex - 1;
        }
        else
        {
            WordStartingXIndex = (WordStartingXIndex + 1) % GridSize;
        }
        l++;
    }
    printf(" Upward Start (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
}

void InsertRightwards(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = (rand() % (GridSize - WordLength + 1));
    int WordStartingYIndex = rand() % GridSize;
    int l, k;
    bool canInsert;
    l = 0;
    while (l < 10)
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex][WordStartingXIndex + k] != '-')
            {
                canInsert = false;
                break;
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
        else if (l == 5)
        {
            WordStartingXIndex = WordStartingXIndex - 1;
        }
        else
        {
            WordStartingYIndex = (WordStartingYIndex + 1) % GridSize;
        }
        l++;
    }
    printf(" Upward Start (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
}

void InsertDiagonalDown(int i, int WordLength, char *argv[], int GridSize)
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
                canInsert = false;
                break;
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
    printf(" Start (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
}

void InsertDiagonalUp(int i, int WordLength, char *argv[], int GridSize)
{
    int WordStartingXIndex = (rand() % (GridSize - WordLength + 1));
    int WordStartingYIndex = GridSize - 1 - (rand() % (GridSize - WordLength + 1));
    int l, k;
    bool canInsert;
    l = 0;
    while (l <= ((GridSize - WordLength + 1) * (GridSize - WordLength + 1)))
    {
        canInsert = true;
        for (k = 0; k < WordLength; k++)
        {
            if (Grid[WordStartingYIndex - k][WordStartingXIndex + k] != '-')
            {
                canInsert = false;
                break;
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
    printf(" Start (%d, %d)\n", WordStartingXIndex, WordStartingYIndex);
}