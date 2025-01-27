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

extern ALLEGRO_FONT *mainFont;
extern ALLEGRO_FONT *titleFont;

/** This function is responsible for looping the game (resetting counters), ending it, or directing the flow
    of events to another action (high scores), depending on the user's choice
    The parameters for this function are the lives and bottle counters, the mouse variables (coordinates and states)
    for button functionality among other uses, the current score, the monster graphic, three logistical boolean
    variables that control the flow of events, and the bin structure
    Void function does not return anything
*/
void gameOver(ALLEGRO_BITMAP *monster, int &livesCounter, bool &playAgain, int mx, int my, bool &mstate,
              bool &pstate, Motion &r, int &i, int &score, bool &doExit, bool &highScores){

    //displays final score
    al_draw_textf(mainFont, WHITE, 480, 850, ALLEGRO_ALIGN_CENTER, "Final Score: %d", score);

    //draws title
    al_draw_text(titleFont, WHITE, 960, 65, ALLEGRO_ALIGN_CENTRE, "Game Over!");

    //draws graphic
    al_draw_bitmap(monster, 650, 300, 0);

    //draws buttons
    al_draw_filled_rectangle(1235, 680, 1645, 805, WHITE);
    al_draw_filled_rectangle(275, 680, 685, 805, WHITE);
    al_draw_filled_rectangle(1235, 830, 1645, 955, WHITE);
    al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "Exit");
    al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "Play Again");
    al_draw_filled_rectangle(1240, 835, 1640, 950, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, FOREGROUND, 1440, 850, ALLEGRO_ALIGN_CENTER, "Add Score");

    //button functionalities
    if (mx >= 280 && my >= 685 && mx <= 680 && my <=800){

        if (mstate){
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "Play Again");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "Play Again");
            //resets counters and resets game for user to play again
            livesCounter = 5;
            r.dx = 3.0;
            score = 0;
            playAgain = true;
        }
        else{
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "Play Again");
        }
    }

    if (mx >= 1240 && my >= 685 && mx <= 1640 && my <=800){

        if (mstate){
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "Exit");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "Exit");
            //stops main game loop and hence exits program
            doExit = true;
        }
        else{
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "Exit");
        }
    }

    if (mx >= 1240 && my >= 835 && mx <= 1640 && my <= 950){

        if (mstate){
            al_draw_filled_rectangle(1240, 835, 1640, 950, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1440, 850, ALLEGRO_ALIGN_CENTER, "Add Score");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(1240, 835, 1640, 950, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1240, 1640, ALLEGRO_ALIGN_CENTER, "Add Score");
            al_draw_text(mainFont, WHITE, 960, 200, ALLEGRO_ALIGN_CENTER, "Enter your one-word username in the console!");
            //runs file functions where user enters in their score and gets to see the list displayed
            highScores = true;
        }
        else{
            al_draw_filled_rectangle(1240, 835, 1640,950, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, FOREGROUND, 1440, 850, ALLEGRO_ALIGN_CENTER, "Add Score");
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;
}
