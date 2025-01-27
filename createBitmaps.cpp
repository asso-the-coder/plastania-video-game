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

using namespace std;


int loadElements(ALLEGRO_BITMAP *&monster, ALLEGRO_BITMAP *&sky, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *&island, ALLEGRO_BITMAP *&bin,
    ALLEGRO_BITMAP *&wheel, ALLEGRO_BITMAP *&slingshot, ALLEGRO_BITMAP *heart[], ALLEGRO_BITMAP *&platform, ALLEGRO_BITMAP *turtles[],
    ALLEGRO_SAMPLE *&endGame, ALLEGRO_SAMPLE *&bottleIn, ALLEGRO_SAMPLE *&bottleOut){

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

    for (int i = 0; i < 5; i++){
        heart[i] = al_load_bitmap("heart.png");
    }
    for (int i = 0; i < 500; i++){
        bottle[i] = al_load_bitmap("WaterBottle.png");
    }

    endGame = al_load_sample("SoundEffectGameOver.ogg");
    bottleIn = al_load_sample("SoundEffectIn.ogg");
    bottleOut = al_load_sample("SoundEffectOut.ogg");

    if (!endGame || !bottleIn || !bottleOut ){
        printf( "Audio clip sample not loaded!\n" );
        return -1;
    }

    if (!monster || !sky || !island || !bin || !wheel || !slingshot || !platform){
        printf( "Image sample not loaded!\n" );
        return -1;
    }

    return 0;

}

void drawGameBitmaps(ALLEGRO_BITMAP *sky, ALLEGRO_BITMAP *slingshot, ALLEGRO_BITMAP *island, ALLEGRO_BITMAP *wheel, ALLEGRO_BITMAP *platform, ALLEGRO_BITMAP *turtles[]){
    al_draw_bitmap(sky, 0,  0, 0);
    al_draw_scaled_bitmap(island, 0, 0, al_get_bitmap_width(island), al_get_bitmap_height(island), -190, 650, 2200, 500, 0);
    al_draw_scaled_bitmap(platform, 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 10, 620, 450, 120, 0);
    al_draw_bitmap(slingshot, 80, 500, 0);
    al_draw_bitmap(wheel, 135, 560, 0);
    al_draw_scaled_bitmap(turtles[0], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 50, 700, 300, 150, 0);
    al_draw_scaled_bitmap(turtles[1], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 70, 500, 300, 150, 0);
    al_draw_scaled_bitmap(turtles[2], 0, 0, al_get_bitmap_width(platform), al_get_bitmap_height(platform), 320, 600, 300, 150, 0);
}

void drawHearts(int livesCounter, ALLEGRO_BITMAP *heart[]){
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
