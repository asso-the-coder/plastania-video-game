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

/** This function displays the main title screen
    The parameters for this function are all the mouse variables (coordinates & states) for button functionality
    among other things, the monster graphics, and three logistical variables that control how the title display branches
    out to other subsets of said display
    Void function does not return anything
*/
void titleScreenDisplay(ALLEGRO_BITMAP *monster, int mx, int my, bool &mstate, bool &pstate, bool &drawTitle, bool &instructions,  bool &credits){

    //draws title
    al_draw_bitmap(monster, 650, 300, 0);
    al_draw_text(titleFont, WHITE, 960, 150, ALLEGRO_ALIGN_CENTRE, "Plastania");

    //draws start button
    al_draw_filled_rectangle(275, 680, 685, 805, WHITE);
    al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "START");

    //start button functionality
    if (mx >= 280 && my >= 685 && mx <= 680 && my <=800){
        if (mstate){
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "START");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "START");
            //moves onto game screen display
            drawTitle = false;
        }
        else{
            al_draw_filled_rectangle(280, 685, 680, 800, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, FOREGROUND, 480, 700, ALLEGRO_ALIGN_CENTER, "START");
        }
    }

    //draws credits button
    al_draw_filled_rectangle(1235, 680, 1645, 805, WHITE);
    al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "CREDITS");

    //credits button functionality
    if (mx >= 1240 && my >= 685 && mx <= 1640 && my <=800){
        if (mstate){
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "CREDITS");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "CREDITS");
            //displays credits tab
            credits = true;
            drawTitle = false;
        }
        else{
            al_draw_filled_rectangle(1240, 685, 1640, 800, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, FOREGROUND, 1440, 700, ALLEGRO_ALIGN_CENTER, "CREDITS");
        }
    }

    //draws how to play button
    al_draw_filled_rectangle(45, 45, 500, 170, WHITE);
    al_draw_filled_rectangle(50, 50, 495, 165, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, WHITE, 270, 65, ALLEGRO_ALIGN_CENTRE, "How To Play");

    //functionality
    if (mx >= 50 && my >= 50 && mx <= 495 && my <= 165){
        if (mstate){
            al_draw_filled_rectangle(50, 50, 495, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 270, 65, ALLEGRO_ALIGN_CENTRE, "How To Play");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(50, 50, 495, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 270, 65, ALLEGRO_ALIGN_CENTRE, "How To Play");
            //displays how to play tab
            instructions = true;
            drawTitle = false;
        }
        else{
            al_draw_filled_rectangle(50, 50, 495, 165, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, WHITE, 270, 65, ALLEGRO_ALIGN_CENTRE, "How To Play");
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;
}

/** This function displays the instructions menu
    The parameters for this function are all the mouse variables (coordinates & states) for button functionality
    among other things, the monster graphics, and three logistical variables that control how the title display branches
    out to other subsets of said display, including the main title screen
    Void function does not return anything
*/
void howToPlay(bool &drawTitle, bool &instructions, ALLEGRO_BITMAP *turtles[], int mx, int my, bool &mstate, bool &pstate){

    //draws instructions & graphics to screen
    al_draw_scaled_bitmap(turtles[2], 0, 0, al_get_bitmap_width(turtles[2]), al_get_bitmap_height(turtles[2]), 1400, 10, 500, 200, 0);
    al_draw_text(titleFont, WHITE, 960, 50, ALLEGRO_ALIGN_CENTRE, "How To Play");
    al_draw_text(mainFont, WHITE, 960, 200, ALLEGRO_ALIGN_CENTRE, "1) Find the water bottle at the tip of the red cannon");
    al_draw_text(mainFont, WHITE, 960, 375, ALLEGRO_ALIGN_CENTRE, "2) Click at the center of the bottle and drag backwards");
    al_draw_text(mainFont, WHITE, 960, 450, ALLEGRO_ALIGN_CENTRE, "as if you would do a slingshot");
    al_draw_text(mainFont, WHITE, 960, 625, ALLEGRO_ALIGN_CENTRE, "3) Release to create the desired trajectory for the");
    al_draw_text(mainFont, WHITE, 960, 700, ALLEGRO_ALIGN_CENTRE, "bottle to go in the bin");
    al_draw_text(mainFont, WHITE, 960, 875, ALLEGRO_ALIGN_CENTRE, "4) The bin moves faster as the score increases. Each");
    al_draw_text(mainFont, WHITE, 960, 950, ALLEGRO_ALIGN_CENTRE, "missed bottle is a life lost. Now save the world!");

    //back button
    al_draw_filled_rectangle(45, 45, 455, 170, WHITE);
    al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");

    //button functionality
    if (mx >= 50 && my >= 50 && mx <= 450 && my <= 165){

        if (mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
            //returns back to main title screen
            drawTitle = true;
            instructions = false;
        }
        else{
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;

}

/** This function displays the credits tab
    The parameters for this function are all the mouse variables (coordinates & states) for button functionality
    among other things, the monster graphics, and three logistical variables that control how the title display branches
    out to other subsets of said display, including the main title screen
    Void function does not return anything
*/
void displayCredits(bool &drawTitle, bool &credits, ALLEGRO_BITMAP *turtles[], int mx, int my, bool &mstate, bool &pstate){

    //draws credits and graphics to screen
    al_draw_scaled_bitmap(turtles[0], 0, 0, al_get_bitmap_width(turtles[0]), al_get_bitmap_height(turtles[0]), 1400, 10, 500, 200, 0);
    al_draw_text(titleFont, WHITE, 960, 50, ALLEGRO_ALIGN_CENTRE, "Credits");
    al_draw_text(mainFont, WHITE, 960, 200, ALLEGRO_ALIGN_CENTRE, "Created By: Abdelgawad Games Corporation");
    al_draw_text(mainFont, WHITE, 960, 300, ALLEGRO_ALIGN_CENTRE, "Senior Developer: Aser Abdelgawad");
    al_draw_text(mainFont, WHITE, 960, 400, ALLEGRO_ALIGN_CENTRE, "Graphics By: Benjamin Chinn");
    al_draw_text(mainFont, WHITE, 960, 500, ALLEGRO_ALIGN_CENTRE, "Music By: DL Sounds");
    al_draw_text(mainFont, WHITE, 960, 600, ALLEGRO_ALIGN_CENTRE, "Sound Effects By: My Instants");
    al_draw_text(mainFont, WHITE, 960, 700, ALLEGRO_ALIGN_CENTRE, "Minecraft Font By: Madpixel Designs");
    al_draw_text(mainFont, WHITE, 960, 800, ALLEGRO_ALIGN_CENTRE, "Special Thanks To:");
    al_draw_text(mainFont, WHITE, 960, 900, ALLEGRO_ALIGN_CENTRE, "Ms. Cullum, Mr. Lafreniere, Joe Zhang, Ryan Xing");


    //back button
    al_draw_filled_rectangle(45, 45, 455, 170, WHITE);
    al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(175, 175, 175));
    al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");

    //button functionality
    if (mx >= 50 && my >= 50 && mx <= 450 && my <= 165){

        if (mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
        else if (pstate && !mstate){
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(100, 100, 100));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
            //returns back to title screen
            drawTitle = true;
            credits = false;
        }
        else{
            al_draw_filled_rectangle(50, 50, 450, 165, al_map_rgb(150, 150, 150));
            al_draw_text(mainFont, WHITE, 250, 65, ALLEGRO_ALIGN_CENTRE, "Back");
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;

}

