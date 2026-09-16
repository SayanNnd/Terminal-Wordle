#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

//colors
#define COLOR_RESET  "\x1b[39;49m"
#define COLOR_BLACK  "\033[40;37m"
#define COLOR_GREEN  "\x1b[42;30m"
#define COLOR_YELLOW "\x1b[43;30m"
#define COLOR_RED    "\x1b[41;30m"
#define COLOR_BLUE   "\x1b[46;30m"
#define NO_OF_WORDS  12979
#define VALID_WORDS  2315

//Loads the file into an array
int load_file(char validWords[][7]) {
    FILE *wordle;
    wordle = fopen("words.txt","r");
    if (wordle == NULL) {
        printf("Error: Could not open words.txt\n");
        return 1;
    }
    for (int i=0; i<NO_OF_WORDS; i++) {
        fgets(validWords[i],7,wordle); 
    }
    fclose(wordle);
    return 0;
}

//Picks word of the day
int word_picker() {
    time_t rawtime;
    time(&rawtime);
    struct tm *local_time = localtime(&rawtime);
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    int shorted = (year*10000)+(month*100)+(day);
    int seed = (shorted * 1103515245 + 12345) & 0x7fffffff;
    return (seed % (VALID_WORDS));
}

int main() {
    char validWords[NO_OF_WORDS][7];

    int loader = load_file(validWords);
    if (loader == 1) {
        printf("Could not succesfully open the file\n");
        printf("Enter any key to exit :- ");
        getchar();
        return 0;
    }

    char word[10];
    strcpy(word, validWords[word_picker()]);
    char guess[20];
    int status = 0;
    printf("*WORDLE*\nGuess the correct word\n");

    gameLogic(guess,word,status,validWords);

    printf("Enter any key to exit :- ");
    getchar();
    return 0;
}