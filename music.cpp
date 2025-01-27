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

/** This function plays the background game music all throughout the game
    There are no parameters for this function
    Returns a 0 if all good, -1 if there are errors like failure to initialize audio
*/
int playMusic(){

    //declaring and initializing main audio sample
    ALLEGRO_SAMPLE *sample = nullptr;

    //loading background music file into the audio sample
    sample = al_load_sample("BlazerRail.wav");

    //checks to ensure audio sample has been loaded
    if (!sample){
        printf( "Audio clip sample not loaded!\n" );
        return -1;
    }

    //loops the sample all throughout the game
    al_play_sample(sample, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    //convey success with no errors
    return 0;
}
