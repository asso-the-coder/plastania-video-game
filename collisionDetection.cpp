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

/** This function calculates the boundary locations for the boundary box for collision detection
    The parameters for this function are the bottle and bin structures, their respective graphics, and the bottle counter
    Void function does not return anything
*/
void calcBounds(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i){
        //calculates bounding box dimensions for collision detection (minimized bounding box for more realistic effect)
        w[i].bbLeft = w[i].posx;
        w[i].bbTop  = w[i].posy + 100;
        w[i].bbRight = w[i].bbLeft + al_get_bitmap_width(bottle[0]);
        w[i].bbBottom = w[i].bbTop + al_get_bitmap_height(bottle[0]) - 100;
        r.bbLeft = r.posx + 30;
        r.bbTop  = r.posy + 10;
        r.bbRight = r.bbLeft + al_get_bitmap_width(bin) - 60;
        r.bbBottom = r.bbTop + al_get_bitmap_height(bin) - 120;
}

/** This function draws the bounding box dimensions and is extremely useful for debugging (however it is not called anywhere)
    The parameters for this function are the bottle and bin structures, their respective graphics, and the bottle counter
    Void function does not return anything
*/
void drawBoundingBox(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i){
    //calculates bounding box dimensions
    calcBounds(w, r, bottle, bin, i);
    //draws bounding boxes
    al_draw_line(w[i].bbLeft, w[i].bbTop, w[i].bbRight, w[i].bbTop, RED, 1);
    al_draw_line(w[i].bbLeft, w[i].bbBottom, w[i].bbRight, w[i].bbBottom, RED, 1);
    al_draw_line(w[i].bbLeft, w[i].bbTop, w[i].bbLeft, w[i].bbBottom, RED, 1);
    al_draw_line(w[i].bbRight, w[i].bbTop, w[i].bbRight, w[i].bbBottom, RED,1);
    al_draw_line(r.bbLeft, r.bbTop, r.bbRight, r.bbTop, RED, 1);
    al_draw_line(r.bbLeft, r.bbBottom, r.bbRight, r.bbBottom, RED, 1);
    al_draw_line(r.bbLeft, r.bbTop, r.bbLeft, r.bbBottom, RED, 1);
    al_draw_line(r.bbRight, r.bbTop, r.bbRight, r.bbBottom, RED,1);
}

/** This function checks if there is a collision between our two objects (if their bounding boxes overlap anywhere)
    The parameters for this function are the bottle and bin structures, their respective graphics, and the bottle counter
    Bool function returns whether or not there is a collision (true/false) to be interpreted by other functions accordingly
*/
bool isCollision(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i) {
    //calculates bounding box dimensions
    calcBounds(w, r, bottle, bin, i);

        //checks every possible scenario to determine where or not a collision is occurring
        if (w[i].bbBottom < r.bbTop) {
            return false;
        }
        else if (w[i].bbTop > r.bbBottom) {
            return false;
        }
        else if (w[i].bbRight < r.bbLeft) {
            return false;
        }
        else if (w[i].bbLeft > r.bbRight) {
            return false;
        }

    //conveys there is a collision
    return true;
}
