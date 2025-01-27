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

/** This function loads the elements of the program (bitmaps and audio samples) with files
    The parameters for this function are all the bitmaps and audio samples in the program
    Returns 0 if success with no errors; returns 1 if there are errors loading the samples and bitmaps
*/
int loadElements(ALLEGRO_BITMAP *&monster, ALLEGRO_BITMAP *&sky, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *&island, ALLEGRO_BITMAP *&bin,
    ALLEGRO_BITMAP *&wheel, ALLEGRO_BITMAP *&slingshot, ALLEGRO_BITMAP *heart[], ALLEGRO_BITMAP *&platform, ALLEGRO_BITMAP *turtles[],
    ALLEGRO_SAMPLE *&endGame, ALLEGRO_SAMPLE *&bottleIn, ALLEGRO_SAMPLE *&bottleOut){

    //loading all bitmaps
    monster = al_load_bitmap("BottleMonster.png");
    sky = al_load_bitmap("SkyScreen.jpg");
    island = al_load_bitmap("Island.png");
    bin = al_load_bitmap("RecyclingBin.png");
    wheel = al_load_bitmap("CannonWheel.png");
    slingshot = al_load_bitmap("CannonBody.png");
    platform = al_load_bitmap("Trapezoid.png");
    turtles[0] = al_load_bitmap("TurtleGreen.png");
    turtles[1] = al_load_bitmap("TurtleBlue.png");
    turtles[2] = al_load_bitmap("TurtleYellow.png");

    //loading bitmap arrays
    for (int i = 0; i < 5; i++){
        heart[i] = al_load_bitmap("heart.png");
    }
    for (int i = 0; i < 500; i++){
        bottle[i] = al_load_bitmap("WaterBottle.png");
    }

    //loading audio samples
    endGame = al_load_sample("SoundEffectGameOver.ogg");
    bottleIn = al_load_sample("SoundEffectIn.ogg");
    bottleOut = al_load_sample("SoundEffectOut.ogg");

    //checking for errors in loading samples
    if (!endGame || !bottleIn || !bottleOut ){
        printf( "Audio clip sample not loaded!\n" );
        return -1;
    }

     //checking for errors loading bitmaps
    if (!monster || !sky || !island || !bin || !wheel || !slingshot || !platform){
        printf( "Image sample not loaded!\n" );
        return -1;
    }

    //conveys success with no errors
    return 0;

}

/** This function draws the game's stationary graphics
    The parameters for this function are all the stationary bitmaps
    Void function does not return anything
*/
void drawGameBitmaps(ALLEGRO_BITMAP *sky, ALLEGRO_BITMAP *slingshot, ALLEGRO_BITMAP *island, ALLEGRO_BITMAP *wheel, ALLEGRO_BITMAP *platform, ALLEGRO_BITMAP *turtles[]){
    //draws all stationary graphics to the game screen
    al_draw_bitmap(sky, 0,  0, 0);
    al_draw_scaled_bitmap(island, 0, 0, al_get_bitmap_width(island), al_get_bitmap_height(island), -190, 650, 2200, 500, 0);
    al_draw_scaled_bitmap(platform, 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 10, 620, 450, 120, 0);
    al_draw_bitmap(slingshot, 80, 500, 0);
    al_draw_bitmap(wheel, 135, 560, 0);
    al_draw_scaled_bitmap(turtles[0], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 50, 700, 300, 150, 0);
    al_draw_scaled_bitmap(turtles[1], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 70, 500, 300, 150, 0);
    al_draw_scaled_bitmap(turtles[2], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 320, 600, 300, 150, 0);
}

/** This function draws the hearts which correspond to the user's remaining lives, dependent on the gameplay
    The parameters for this function are the lives counter, and the heart graphics
    Void function does not return anything
*/
void drawHearts(int livesCounter, ALLEGRO_BITMAP *heart[]){
    //depending on the user's lives count, draws hearts
    if (livesCounter == 5){
        al_draw_bitmap(heart[0], 20, 20, 0);
        al_draw_bitmap(heart[1], 120, 20, 0);
        al_draw_bitmap(heart[2], 220, 20, 0);
        al_draw_bitmap(heart[3], 320, 20, 0);
        al_draw_bitmap(heart[4], 420, 20, 0);
    } else if (livesCounter == 4){
        al_draw_bitmap(heart[0], 20, 20, 0);
        al_draw_bitmap(heart[1], 120, 20, 0);
        al_draw_bitmap(heart[2], 220, 20, 0);
        al_draw_bitmap(heart[3], 320, 20, 0);
    } else if (livesCounter == 3){
        al_draw_bitmap(heart[0], 20, 20, 0);
        al_draw_bitmap(heart[1], 120, 20, 0);
        al_draw_bitmap(heart[2], 220, 20, 0);
    } else if (livesCounter == 2){
        al_draw_bitmap(heart[0], 20, 20, 0);
        al_draw_bitmap(heart[1], 120, 20, 0);
    } else if (livesCounter == 1){
        al_draw_bitmap(heart[0], 20, 20, 0);
    }
}

