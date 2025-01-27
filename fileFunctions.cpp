#include <iostream>
#include <stdio.h>
#include "defines.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//bringing over global variables from another file
extern ALLEGRO_FONT *mainFont;
extern ALLEGRO_FONT *titleFont;

/** This function sorts the game's high scores (stored in the text file in descending order and saves them to user struct
    The parameters for this function are the text file, the user structure, the current score, and the player counter
    Returns 0 if success with no errors; returns 1 if there are errors accessing the text file
*/
int sortHighScores(int score, User p[], int &counter, FILE *fptr){

    //opens file to read
    fptr = fopen("highscores.txt", "r");

    //checks if file opens properly (if it exists)
    if (!fptr){
        printf("File doesn't exist.");
        return 1;
    }

    /*reads in information from file into the user struct until the file ends; in the meantime, a counter keeps track
    of the number of entries in the file*/
    while (!feof(fptr)){
        fscanf(fptr, "%s", p[counter].username);
        fscanf(fptr, "%d", &p[counter].highscore);
        //increments player counter
        counter++;
    }

    //asks user for input to save it into the user struct
    printf("Enter your one-word username:\n");
    scanf("%s", p[counter - 1].username);

    //saving the current score into the user struct
    p[counter - 1].highscore = score;

    //declaring temporary switch variables for the sorting process
    int switchScore = 0;
    char switchName[20];

    //sorts the struct in descending order of score (each score is accompanied by a username)
    for (int i = 0; i < counter; i++){
        for (int j = 0; j < counter; j++){
            if(p[i].highscore > p[j].highscore){
                switchScore = p[i].highscore;
                p[i].highscore = p[j].highscore;
                p[j].highscore = switchScore;

                strcpy(switchName, p[i].username);
                strcpy(p[i].username, p[j].username);
                strcpy(p[j].username, switchName);
            }
        }
    }

    //closes file
    fclose(fptr);

    //conveys success with no errors
    return 0;

}

/** This function writes the game's newly sorted high scores to the text file
    The parameters for this function are the user structure, the current score, the player counter, two logistical
    boolean variables that control what is displayed on the screen, and the text file
    Returns 0 if success with no errors; returns 1 if there are errors accessing the text file
*/
int inputHighScores(int score, User p[], int &counter, FILE *fptr, bool &highScores, bool &displayScores){

    //opens text file to write to it
    fptr = fopen("highscores.txt", "w");

    //checks if file opened properly (if it exists)
    if (!fptr){
        printf("File doesn't exist.");
        return 1;
    }

    //writes to the text file the information saved in the user struct
    for (int i = 0; i < counter; i++){
        fprintf(fptr, "%s", p[i].username);
        fprintf(fptr, " ");
        fprintf(fptr, "%d", p[i].highscore);
        fprintf(fptr, "\n");
    }

    //closes text file
    fclose(fptr);

    //commands user to look at the newly formed display (created in the very next function)
    printf("\nRETURN TO GAME SCREEN!\n");

    //initializing variables that control what is being displayed... this displays the sorted high score list
    displayScores = true;
    highScores = false;

    //conveys success with no errors
    return 0;

}

/** This function displays the game's sorted high scores
    The parameters for this function are the user structure, the mouse variables (coordinates and states) for button
    functionality, the player counter, & one logistical boolean variable that controls what is displayed on the screen
    Returns 0 if success with no errors
*/
int displayHighScores(User p[], int &counter, bool &displayScores, int mx, int my, bool &mstate, bool &pstate){

    //draws a title
    al_draw_text(titleFont, WHITE, 960, 50, ALLEGRO_ALIGN_CENTER, "Highscores");

    //displays top eight scores to the screen
    for (int i = 0; i < 8; i++){
        al_draw_textf(mainFont, WHITE, 480, 100*i + 200, ALLEGRO_ALIGN_CENTER, "%s", p[i].username);
        al_draw_textf(mainFont, WHITE, 1440, 100*i + 200, ALLEGRO_ALIGN_CENTER, "%d", p[i].highscore);
    }

    //draws back button
    al_draw_filled_rectangle(45, 45, 455, 170, WHITE);
    al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");

    //back button functionality
    if (mx >= 50 && my >= 50 && mx <= 450 && my <= 165){
        if (mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
            //returns back to game over screen by stopping the high score display
            displayScores = false;
        }
        else{
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;

    //conveys success with no errors
    return 0;

}
