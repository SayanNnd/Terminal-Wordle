#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NO_OF_WORDS  12979

typedef struct {
    int max_streak;
    int current_streak;
} streak;

typedef struct {
    int date;
    int status;
    int wordsPlayed;
    char wordsUsed[6][20];
} today;

int gameLogic(char word[10], char validWords[NO_OF_WORDS][7],today tdy,int date);
int word_check(char word[10], char validWords[][7]);