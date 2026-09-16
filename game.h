#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NO_OF_WORDS  12979

void gameLogic(char guess[20],char word[10],int status, char validWords[NO_OF_WORDS][7]);
int word_check(char word[10], char validWords[][7]);