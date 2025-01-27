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

/** This function plays the background game music all throughout the game
    The parameters for this function are all the mouse variables (coordinates & states)
    Void function does not return anything
*/
void slingShot(int mx, int my, bool &mstate, bool &pstate, bool &clicked){

    //al_draw_circle(350, 560, 75, WHITE, 5);
    //al_draw_circle(350, 560, 300, WHITE, 5);

    //declaring and initializing variables
    float distanceFromCenter = calculateDistance(mx, my, 350, 560);
    int distX, distY;
    distX = abs(350 - mx);
    distY = abs(560 - my);

    /*checks if mouse coordinates are within a certain radius around the bottle, in which the user is expected to
    begin dragging the bottle*/
    if (distanceFromCenter < 75){
        if (mstate){
            clicked = true;
        }
    }

    //checks that mouse is held down
    if (clicked){
        if (mstate){
            /*checks if mouse coordinates are within a certain larger radius around the bottle (boundary), and
            if so, the slingshot line is drawn without a problem*/
            if (distanceFromCenter < 300){
                al_draw_circle(mx, my, 30, WHITE, 5);
                al_draw_line(350, 560, mx, my, BLACK, 8);
                al_draw_line(350, 560, mx, my, BROWN, 6);
            }
            else{
                /*if the mouse coordinates are farther than the boundary, the slingshot line is kept within the boundaries
                by shortening the length from the center... the x and y coordinates of the mouse create a triangle with the
                length from the center, and therefore a similarity ratio is used to minimize the triangle's size (and hence the
                hypotneuse) to shorten the length from the center to keep it within the boundaries while still
                maintaining the triangle's inner ratio*/
                float similarityRatio = 300 / distanceFromCenter;
                float lengthFromCenter = distX*similarityRatio;
                float heightFromCenter = distY*similarityRatio;

                //draws the slingshot line at different locations with respect to the center depending on the mouse coordinates
                if (mx < 350 && my < 560){
                    al_draw_circle(350-lengthFromCenter, 560-heightFromCenter, 30, WHITE, 5);
                    al_draw_line(350, 560, 350-lengthFromCenter, 560-heightFromCenter, BLACK, 7);
                    al_draw_line(350, 560, 350-lengthFromCenter, 560-heightFromCenter, BROWN, 6);
                }
                else if (mx > 350 && my < 560){
                    al_draw_circle(350+lengthFromCenter, 560-heightFromCenter, 30, WHITE, 5);
                    al_draw_line(350, 560, 350+lengthFromCenter, 560-heightFromCenter, BLACK, 7);
                    al_draw_line(350, 560, 350+lengthFromCenter, 560-heightFromCenter, BROWN, 6);
                }
                else if (mx < 350 && my > 560){
                    al_draw_circle(350-lengthFromCenter, 560+heightFromCenter, 30, WHITE, 5);
                    al_draw_line(350, 560, 350-lengthFromCenter, 560+heightFromCenter, BLACK, 7);
                    al_draw_line(350, 560, 350-lengthFromCenter, 560+heightFromCenter, BROWN, 6);
                }
                else if (mx > 350 && my > 560){
                    al_draw_circle(350+lengthFromCenter, 560+heightFromCenter, 30, WHITE, 5);
                    al_draw_line(350, 560, 350+lengthFromCenter, 560+heightFromCenter, BLACK, 7);
                    al_draw_line(350, 560, 350+lengthFromCenter, 560+heightFromCenter, BROWN, 6);
                }

            }

        }

        //checks that mouse is released
        if (pstate && !mstate){
            clicked = false;
        }
    }

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;
}

/** This function calculates the distance between two points on the 2D plane (display)
    The parameters for this function are two coordinates and their respective positions
    Returns the answer to the aforementioned calculation in float format
*/
float calculateDistance(float x1, float y1, float x2, float y2){
    //this equation is based on the distance between two points on a Cartesian plane, and can be reused for any 2D plane
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

/** This function calculates the trajectory of the water bottle with respect to physically accurate projectile motion
    The parameters for this function are all the mouse variables (coordinates & states), the bottle & time counters,
    the bottle graphic, and the bottle structure
    Void function does not return anything
*/
void calculateTrajectory(Motion w[], int mx, int my, bool &pstate, bool &mstate, int t, bool &clicked
    , ALLEGRO_BITMAP *bottle[], int &i, int &prevI){

    //increasing the time counter by one in correspondence with the timer (for the kinematics equations)
    t += 1;

    //declaring and initializing variables
    int distanceX = abs(350 - mx);
    int distanceY = abs(560 - my);

    //checking if mouse is held down
    if (mstate){
        clicked = true;
    }


    if (clicked){

        //at the point of release
        if (pstate && !mstate){
            //calculates the angle between the center and the point of release in relation to the horizontal
            w[i].angle = atan(distanceY/distanceX);
            //separates motion into horizontal and vertical components and obtains a velocity for each
            w[i].initialVelocityx = ((calculateDistance(350, 560, mx, my)*0.6) * cos(w[i].angle * (180/M_PI)));
            w[i].initialVelocityy = ((calculateDistance(350, 560, mx, my)*0.6) * sin(w[i].angle * (180/M_PI)));

            //produces a constant speed for the horizontal component, and an accelerating speed for vertical component
            w[i].dx = w[i].initialVelocityx * t;
            w[i].dy = ((w[i].initialVelocityy * t) + (40.0 * pow(t, 2)));
        }

        //checks if there is a new bottle on deck
        if (i == prevI && !mstate){
                /*adds horizontal/vertical displacements to their respective positions separately (this works due to
                the principle of orthogonality*/
                w[i].posx += w[i].dx * 0.12;
                w[i].posy -= w[i].dy * 0.12;
                //creates a parabolic, gravitational effect
                w[i].dy -= 3.0;
        //otherwise turns the current bottle counter value into the previous one as a new one comes along
        } else if (i != prevI){
            prevI = i;
            clicked = false;
        }
    }

    //draws the bottle w/ respect to the aforementioned laws of physics
    al_draw_bitmap(bottle[i], w[i].posx, w[i].posy, 0);

    //the current mouse state becomes the previous one as a new one comes along
    pstate = mstate;

}

/** This function moves the recycle bin forwards and backwards while also increasing its speed with respect to gameplay
    The parameters for this function are the bottle and bin structures, their graphics, the bottle counter, and the
    "forwards" logistical variable that determines forwards vs backwards motion
    Void function does not return anything
*/
void moveBin(Motion &r, Motion w[], ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i, bool &f){

    //checks if there is a collision between the bottle and the bin and increases the speed accordingly
    if (isCollision(w, r, bottle, bin, i)){
        r.dx += 1.0;
        //sets a max speed
        if (r.dx > 15.0){
            r.dx = 15.0;
        }
    }

    //checks if the bottle is moving forwards and adds a positive displacement
    if (f && r.posx < 1640 && r.posx >= 1140){
        r.posx += r.dx;
    }
    //as soon as it reaches a certain point moving forwards, it turns around quickly and begins moving backwards
    else if (f && r.posx >= 1640){
        f = false;
        r.posx -= 15;
    }

    //checks if the bottle is moving backwards and adds a negative displacement
    if (!f && r.posx > 1140 && r.posx <= 1640){
        r.posx -= r.dx;
    }
    //as soon as it reaches a certain point moving backwards, it turns around quickly and begins moving forwards
    else if (!f && r.posx <= 1140){
        f = true;
        r.posx += 15;
    }

    //draws the bin in the above calculated position
    al_draw_bitmap(bin, r.posx,  r.posy, 0);

}

