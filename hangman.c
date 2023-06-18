/* I started this hangman game when I was about 3 weeks into Harvard's CS50 course
   I just watched the "week 6" lecture.  I'm very new to programming (about 1 month).
   Anyway I'm really proud of this little command line hangman game. */

#define _XOPEN_SOURCE 500
#define MAXWORDLENGTH 12
#define MINWORDLENGTH 3
#define MAXARRAYLENGTH 12
#define MINTRIES 5

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


void clear(void);
void PrintGreetMessage(void);
void fillblank(char *a, char *b);
void swap(char *a, char *b);
void play(char *player1word, char*player2guess, char*undsArray, char*chardumpArray);
void PrintBoard(int casenum);
void printHangmanStand(int numLines);
int readWord(char *buf, int bufSize);


int main(void)
{
  
    char word[MAXARRAYLENGTH];
    char guess[MAXARRAYLENGTH];
    char empty[MAXARRAYLENGTH];
    char abyss[MAXARRAYLENGTH];      
  
  
    PrintGreetMessage();
   
    printf("Word must not contain spaces or numbers\n");
    printf("Word must be lowercase\n\n");
    printf("Please enter a word for player 2 to try and figure out: ");
    fgets(word, 20, stdin);
    
    int alphacheck = 0;
    int n = strlen(word);
    int x = 0;

    do {

        if((isalpha(word[x]) && (n < MAXWORDLENGTH) && (n > MINWORDLENGTH)  && (islower(word[x]))))
        {
            x++;
            if(x == (n - 1))
            {
                alphacheck = 1;
            }
        }

        else
        {
            printf("\n\nPlayer 1, please enter a valid word: ");
            readWord(word, MAXWORDLENGTH);
            alphacheck = 0;
            n = strlen(word);
            x = 0;
        }
    }while(alphacheck == 0);

    clear();

    //initialize these 2 arrays
    int a = 0;
    
    while(a < n)
    {
        empty[a] = '_';
        abyss[a] = '_';
        a++;
    }

    empty[strlen(word) - 1] = '\0';
    abyss[strlen(word) - 1] = '\0';
    guess[strlen(word) - 1] = '\0';
    word[strlen(word) - 1] = '\0';

    play(word, guess, empty, abyss);


printf("\n");

return 0;
}



//Functions!!!!!

void PrintBoard(int casenum)
{
    switch (casenum)
    {
        case 1:
        printf("|\\___\n");
        printHangmanStand(7);
        break;
        
        case 2:
        printf("|\\___\n");
        printf("|   O\n");
        printf("|   |\n");
        printHangmanStand(5);
            break;
        
        case 3:
        printf("|\\___\n");
        printf("|   O\n");
        printf("|  /|\n");
        printHangmanStand(5);
            break;
        
        case 4:
        printf("|\\___\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printHangmanStand(5);        
            break;  
            
        case 5:
        printf("|\\___\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printf("|  / \n");
        printHangmanStand(4);       
            break; 
            
        case 6:
        printf("|\\___\n");
        printf("|   O\n");
        printf("|  /|\\\n");
        printf("|  / \\\n");
        printHangmanStand(4);        
            break;
            
        default: 
        printf("Error: switch case not met\n\n");
    }
}

void fillblank(char *a, char *b)
{
    char tmp = *a;
    //*a = *b;
    *b = tmp;
}

void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void printHangmanStand(int numLines) 
{
    while(numLines > 0) 
    {
        printf("|\n");
        numLines --;
    }
}

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


void PrintGreetMessage(void)
{
    clear();
    printf("\n\n\nWELCOME TO MARTY'S HANGMAN!!! HEHEHhahaHEhaheHahe\n");
    printf("\n");
    usleep(200000);
}

void play(char *player1word, char*player2guess, char*undsArray, char*chardumpArray)
{

int wordlength = strlen(player1word); 
int RemainingGuesses = 5;
int letterfound = 0;
int timesfound = 0;
int casenum = 1;
char enterpress;
    
        PrintBoard(casenum);
        
        for(int z = 0; z < wordlength; z++)
        {
            printf(" %c ", undsArray[z]);
        }

        for(int i = 0; i < (wordlength * MINTRIES); i++)
        {
            letterfound = 0;
            printf("\n\n");
            printf("Please make a guess: ");
            scanf("%c", &player2guess[i]);
            enterpress = getchar();
            printf("\n\n");



            for(int b = 0; b < wordlength; b++)
            {
                if(player2guess[i] == player1word[b]) 
                {
                    letterfound = 1;
                    fillblank(&player2guess[i], &undsArray[b]);
                    swap(&player1word[b], &chardumpArray[b]);
                    timesfound++;
                    
                }
            }
            
            if(letterfound == 0)
            {
                casenum++;
                printf("\nYou have %i tries left!\n", --RemainingGuesses);
            }

            if(timesfound == wordlength)
            {
                PrintBoard(casenum);
                for(int v = 0; v < wordlength; v++)
                {
                    printf(" %c ", undsArray[v]);
                }
                printf("\n\n   WOW You figured out player 1's word!!!\n\n\n");
                printf("    You win!!!!!!!!\n\n\n");
                break;
            }
            if(RemainingGuesses == 0)
            {
                casenum = 6;
                PrintBoard(casenum);
                printf("\n\n\n YOU LOSE HEHEHEHEHEHEH \n\n");
                break;
            }
            PrintBoard(casenum);
            for(int j = 0; j < wordlength; j++)
            {
                printf(" %c ", undsArray[j]);
            }
        }
}


int readWord(char *buf, int bufSize)
{
    if(fgets(buf, bufSize, stdin) == NULL) 
    {
        return 0;
    }

    return 1;
}