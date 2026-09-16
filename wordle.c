#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

#define NO_OF_WORDS  12979
#define VALID_WORDS  2315
#define BOLD "\033[1m"
#define RESET "\033[0m"

streak str = {0};
today tdy = {.date = 0, .status=0, .wordsPlayed=0, .wordsUsed={}};

int load_file(char validWords[][7]);
int word_picker();
void openStreak();

//------------------------------------------------------------------------------------------------------------------

int main() {
    openStreak();
    char validWords[NO_OF_WORDS][7];

    int loader = load_file(validWords);
    if (loader == 1) {
        printf("Could not succesfully open the file\n");
        printf("Enter any key to exit :- ");
        getchar();
        return 0;
    }
    int date = date_picker();

    //Picks the daily word
    int seed = ((date * 1103515245 + 12345) & 0x7fffffff) % VALID_WORDS;
    char word[10];
    strcpy(word, validWords[seed]);
    printf("*WORDLE*\nGuess the correct word\n");

    int result = gameLogic(word,validWords,tdy,date);

    if (result==1) {
        str.current_streak++;
        if (str.current_streak>str.max_streak) str.max_streak = str.current_streak;
    }
    else if (result==0) {
        str.current_streak=0;
    }
    else if (result==2) {
        printf(BOLD"\nTHIS WAS AN ALREADY PLAYED GAME...COME BACK TOMORROW\n"RESET);
    }

    printf("\nThe Current Win Streak is :- %d\n",str.current_streak);
    printf("Your Maximum WIn Streak is :- %d\n",str.max_streak);


    FILE* file_ptr;
    file_ptr = fopen("data.bin","rb+");
    int write = fwrite(&str,sizeof(streak),1,file_ptr);
    if (write != 1) {
        printf("Error in writing the streak changes....");
        return 1;
    }
    fclose(file_ptr);

    printf("Enter any key to exit :- ");
    getchar();
    return 0;
}

//------------------------------------------------------------------------------------------------------------------

//Loads the valid words into an array
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

//Produces today's daye
int date_picker() {
    time_t rawtime;
    time(&rawtime);
    struct tm *local_time = localtime(&rawtime);
    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    int shorted = (year*10000)+(month*100)+(day);
    return shorted;
}

//Loads streak file
void openStreak(){
    FILE *file_ptr;
    file_ptr = fopen("data.bin","wbx");
    if (file_ptr!=NULL) {
        printf("Bin file not found!!....Creating a new bin file\n");
        size_t written = fwrite(&str,sizeof(streak),1,file_ptr);
        if (written!=1) {
            printf("Bin file could not be created...Try again\n");
        }
        written = fwrite(&tdy,sizeof(today),1,file_ptr);
        if (written==1) {
            printf("Succesfully written into the new bin file....\n");
        }
        else {
            printf("Bin file could not be created...Try again\n");
        }
        fclose(file_ptr);
    }
    else {
        file_ptr = fopen("data.bin","rb+");
        if (file_ptr == NULL) {
            printf("Error opening file for reading");
        }
        size_t read = fread(&str,sizeof(streak),1,file_ptr);
        fclose(file_ptr);
    }
}