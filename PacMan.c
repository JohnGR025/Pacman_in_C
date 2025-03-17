/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> /*Windows-specific for keyboard input*/
#include <windows.h> /*For Sleep function*/

/*Constants*/
#define ROWS 11
#define COLS 19

/*Functions Prototypes*/
void area(char board[][19]);
void preparing_board(char board[][19], int ghosts[], int pacman[], int num);
void move_pacman(char board[][19],int pacman[], int* moves);
void move_ghosts(char board[][19], int ghosts[], int pacman[], int num);
int alive(int pacman[], int ghosts[], int num);

int main(void)
{
    srand(time(NULL));
    /*Variables Declaration*/
    /*Useful stuff*/
    int option, difficulty=2, moves=0;
    char ch;
    /*The characters*/
    int ghosts[6], pacman[2]={7, 9};
    /*The Board Game*/
    char board[ROWS][COLS]={
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
        {'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b'},
        {'b', 'o', 'b', 'o', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'o', 'b', 'o', 'b'},
        {'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b'},
        {'b', 'b', 'b', 'o', 'b', 'b', 'o', 'b', 'o', 'o', 'o', 'b', 'o', 'b', 'b', 'o', 'b', 'b', 'b'},
        {'t', 'o', 'o', 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'o', 'o', 't'},
        {'b', 'b', 'b', 'o', 'b', 'b', 'o', 'b', 'b', 'b', 'b', 'b', 'o', 'b', 'b', 'o', 'b', 'b', 'b'},
        {'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'p', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b'},
        {'b', 'o', 'b', 'b', 'b', 'b', 'b', 'o', 'b', 'b', 'b', 'o', 'b', 'b', 'b', 'b', 'b', 'o', 'b'},
        {'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b', 'o', 'b', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b'},
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}
    };

    /*Menu*/
    printf("\n*****PAC MAN*****\n\n");
    printf("Welcome Player!!!\n");
    do 
    {
        do
        {
            printf("1) Play\n");
            printf("2) Settings\n");
            printf("3) Quit\n");
            printf("Choose an option: ");
            scanf("%d", &option);
        } while (option<1 || option>3);
        while (((ch = getchar()) != '\n') && (ch != EOF)); /*Flush the Buffer*/

        switch (option)
        {
        case 1: /*PLay*/
            /*Printing the game board*/
            preparing_board(board, ghosts, pacman, difficulty);
            system("cls");
            printf("\n*****PAC MAN*****\n");

            do
            {
                printf("\n*****PAC MAN*****\n");
                area(board);
                move_pacman(board, pacman, &moves);
                if (!alive(pacman, ghosts, difficulty))
                    break;
                move_ghosts(board, ghosts, pacman, difficulty);

                system("cls"); /*Clear screen for next frame*/
            } while (alive(pacman, ghosts, difficulty));
            
            printf("You Died!!!\n");
        break;
        
        case 2: /*Settings*/
            do
            {
                printf("Choose difficulty: ");
                scanf("%d", &difficulty);
            } while (difficulty<1 || difficulty>4);
            printf("\n");
        break;
        }
    } while (option!=3);

    printf("You manage to move %d times\n", moves);
    return 0;
}

/*Function Factory*/
void area(char board[][19])
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            switch (board[i][j])
            {
            case 'b':
                printf("%c", '#');
            break;

            case 'o':
            case 't':
                printf(" ");
            break;

            case 'g':
                printf("G");
            break;

            case 'p':
                printf("C");
            break;
            }
        }
        printf("\n");
    }
    
}

void preparing_board(char board[][19], int ghosts[], int pacman[], int num)
{
    int i;

    for (i = 0; i < num*2; i+=2)
    {
        do
        {
            ghosts[i] = rand()%ROWS;
            ghosts[i+1] = rand()%COLS;
        } while ((board[ghosts[i]][ghosts[i+1]]=='b') || (ghosts[i]==7) || (ghosts[i+1]==9));
        board[ghosts[i]][ghosts[i+1]] = 'g';
    }
    pacman[0] = 7;
    pacman[1] = 9;
    
}

void move_pacman(char board[][19], int pacman[], int* moves)
{
    char move, ch;
    int flag=1, temp1=pacman[0], temp2=pacman[1];

    do
    {
        printf("\nChoose a direction (a,s,d,w) or 'q' to quit:");
        /* Wait for a key press */
        while (!_kbhit()) /*No delay between checks to respond immediately to input*/
            Sleep(10); /*Small delay to prevent CPU hogging*/

        move = _getch(); /*Get the key press*/
        if (move == 'q') /* Quit option */ 
        {
            printf("\nQuitting game...\n");
            return;
        }
    } while (!((move=='w') || (move=='a') || (move=='s') || (move=='d')));
    
    switch (move)
    {
    case 'w': /*Up*/
        if (pacman[0]-1>0)
            if (board[pacman[0]-1][pacman[1]]!='b')
            {
                pacman[0]--;
                (*moves)++;
            }
    break;
    
    case 'a': /*Left*/
        if (pacman[1]-1>=0)
        {
            if (board[pacman[0]][pacman[1]-1]=='t')
                {
                    pacman[1] = 17;
                    (*moves)++;
                }
            else if (board[pacman[0]][pacman[1]-1]!='b')
                {
                    pacman[1]--;
                    (*moves)++;
                }
        }
    break;

    case 's': /*Down*/
        if (pacman[0]+1<ROWS)
            if (board[pacman[0]+1][pacman[1]]!='b')
            {
                pacman[0]++;
                (*moves)++;
            }
    break;

    case 'd': /*Right*/
        if (pacman[1]+1<=COLS)
        {
            if (board[pacman[0]][pacman[1]+1]=='t')
            {
                pacman[1] = 1;
                (*moves)++;
            }
            else if (board[pacman[0]][pacman[1]+1]!='b')
            {
                pacman[1]++;
                (*moves)++;
            }
        }
    break;
    }
    board[temp1][temp2] = 'o';
    board[pacman[0]][pacman[1]] = 'p';
    printf("Row: %d\nCol: %d\n", pacman[0], pacman[1]);
}

void move_ghosts(char board[][19], int ghosts[], int pacman[], int num)
{
    int i, move, direction, flag, temp;
    int temp1, temp2;

    for (i = 0; i < num*2; i+=2)
    {
        temp1 = ghosts[i];
        temp2 = ghosts[i+1];

        /*Chase Sequence*/
        /*Move towards pacman*/
        /*Same Row*/
        if ((pacman[1]<ghosts[i+1]) && ((ghosts[i+1]-1)=='o'))
        {    
            ghosts[i+1] -= 1;
            board[temp1][temp2] = 'o';
            board[temp][ghosts[i+1]] = 'g';
            continue;
        }
        else if ((pacman[1]>ghosts[i+1]) && ((ghosts[i+1]+1)=='o'))
        {
            ghosts[i+1] += 1;
            board[temp1][temp2] = 'o';
            board[temp][ghosts[i+1]] = 'g';
            continue;
        }
        /*Same Column*/
        if ((pacman[0]<ghosts[i]) && ((ghosts[i]-1)=='o'))
        {    
            ghosts[i] -= 1;
            board[temp1][temp2] = 'o';
            board[ghosts[i]][temp] = 'g';
            continue;
        }
        else if ((pacman[0]>ghosts[i]) && ((ghosts[i]+1)=='o'))
        {
            ghosts[i] += 1;
            board[temp1][temp2] = 'o';
            board[ghosts[i]][temp] = 'g';
            continue;
        }
        
        /*Movement*/
        do
        {
            flag = 0;

            move = rand()%2; /*move a tile (for move=1) or not (for move=0)*/
            direction = (rand()%3)-1; /*move accordingly to move (forward or backward)*/
            temp = ghosts[move+i]+direction; /*store the updated movement*/

            if (move==0)
            {
                if ((temp<=0) || (temp>=ROWS))
                    flag = 1;
            }
            else
                if ((temp<=0) || (temp>=COLS))
                    flag = 1;
                    
            if (flag==1)
                continue;

            if (move==0)
            {
                if (board[temp][ghosts[i+1]]!='o')
                    flag = 1;
            }
            else
                if (board[ghosts[i]][temp]!='o')
                    flag = 1;
        } while (flag);

        /*Finilizing the changes (movements)*/
        ghosts[move+i] += direction;
        board[temp1][temp2] = 'o';
        if (move==0)
            board[temp][ghosts[i+1]] = 'g';
        else
            board[ghosts[i]][temp] = 'g';
    }
}

int alive(int pacman[], int ghosts[], int num)
{
    int i;
    for (i = 0; i < num*2; i+=2)
        if ((pacman[0]==ghosts[i]) && (pacman[1]==ghosts[i+1]))
            return 0; 
    
    return 1;
}