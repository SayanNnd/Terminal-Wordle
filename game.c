#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//colors
#define COLOR_RESET  "\x1b[39;49m"           
#define COLOR_BLACK  "\033[40;37m"
#define COLOR_GREEN  "\x1b[42;30m"
#define COLOR_YELLOW "\x1b[43;30m"
#define COLOR_RED    "\x1b[41;30m"
#define COLOR_BLUE   "\x1b[46;30m"
#define NO_OF_WORDS  12979
#define VALID_WORDS  2315

int word_check(char word[10], char validWords[][7]) {
    int low = 0;
    int high = VALID_WORDS-1;
    while (low<=high){
        int mid = (low+high)/2;
        int comp = strcasecmp(word,validWords[mid]);
        if (comp == 0){
            return 0;
        }
        else if(comp > 0){
            low = mid+1;
        }
        else {
            high = mid-1;
        }
    }
    low = VALID_WORDS;
    high = NO_OF_WORDS-1;
    while (low<=high){
        int mid = (low+high)/2;
        int comp = strcasecmp(word,validWords[mid]);
        if (comp == 0){
            return 0;
        }
        else if(comp > 0){
            low = mid+1;
        }
        else {
            high = mid-1;
        }
    }
    return 1;
}

void gameLogic(char guess[20],char word[10],int status, char validWords[][7]){
    for (int i=1; i<=6; i++) {
        fgets(guess, 20, stdin);
        if (status == 1) {
            printf("\x1b[A\x1b[2K");
        }
        printf("\x1b[A\x1b[2K");

        if (strlen(guess) != 6) {
            printf(COLOR_RED "Please Enter a 5-Letter Word" COLOR_RESET "\n");
            status = 1;
            i--;
            continue;
        }
        int resp = word_check(guess, validWords);
        if (resp == 1) {
            printf(COLOR_RED "Please Enter a valid Word" COLOR_RESET "\n");
            status = 1;
            i--;
            continue;
        }

        char hash[10];
        char colors[5][10] = {COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK}; 
        strcpy(hash,word);     
        int checker = 0;
        
        //word comparision
        for (int j=0; j<5; j++) {
            if (toupper(guess[j]) == toupper(hash[j])) {
                hash[j] = '\0';
                strcpy(colors[j],COLOR_GREEN);
                checker++;
            }
        }
        for (int j=0; j<5; j++) {
            if (strcmp(colors[j], COLOR_GREEN) == 0) continue;
            for (int t = 0; t < 5; t++) {
                if (hash[t] != '\0' && toupper(guess[j]) == toupper(hash[t])) {
                    strcpy(colors[j], COLOR_YELLOW);
                    hash[t] = '\0';
                    break;
                }
            }    
        }

        //print the word
        for (int j=0; j<5; j++) {
            printf("%s %c "COLOR_RESET " ",colors[j],toupper(guess[j]));
        }
        printf("\n");

        //win condition
        if (checker == 5) {
            printf("CONGRATS!!\n");
            break;
        }

        //lose condition
        if (i == 6) {
            printf("You Lost!!\n");
            for (int k = 0; k < 5; k++) {
                printf(COLOR_BLUE " %c " COLOR_RESET " ",toupper(word[k]));
            }
            printf(" was the correct word.\nBetter Luck Tomorrow\n");
            break;
        }
        status = 0;
    }
}