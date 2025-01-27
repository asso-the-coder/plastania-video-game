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

using namespace std;


void slingShot(int mx, int my, bool &mstate, bool &pstate, bool &clicked){

    //al_draw_circle(350, 560, 75, WHITE, 5);
    //al_draw_circle(350, 560, 300, WHITE, 5);

    float distanceFromCenter = calculateDistance(mx, my, 350, 560);

    int distX, distY;
    distX = abs(350 - mx);
    distY = abs(560 - my);

    //cout << distX << " " << distY << endl;

    if (distanceFromCenter < 75){
        if (mstate){
            clicked = true;
        }
    }
    if (clicked){
        if (mstate){

            if (distanceFromCenter < 300){
                al_draw_circle(mx, my, 30, WHITE, 5);
                al_draw_line(350, 560, mx, my, BLACK, 8);
                al_draw_line(350, 560, mx, my, BROWN, 6);
            }
            else{
                float congruenceRatio = 300 / distanceFromCenter;
                //cout << congruenceRatio << endl;
                float lengthFromCenter = distX*congruenceRatio;
                float heightFromCenter = distY*congruenceRatio;
                //cout << lengthFromCenter << " " << heightFromCenter << endl;


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
        if (pstate && !mstate){
            clicked = false;
            //cout << "RELEASE" << endl;
        }
    }

    pstate = mstate;
}

float calculateDistance(float x1, float y1, float x2, float y2){
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

void calculateTrajectory(Motion w[], int mx, int my, bool &pstate, bool &mstate, int t, bool &clicked
    , int &r, ALLEGRO_BITMAP *bottle[], int &i, int &prevI){

    t += 1;

    r %= 8 + 1;

    int distanceX = abs(350 - mx);
    int distanceY = abs(560 - my);

    if (mstate){
        clicked = true;
    }

    if (clicked){
        if (pstate && !mstate){
            w[i].angle = atan(distanceY/distanceX);
            w[i].initialVelocityx = ((calculateDistance(350, 560, mx, my)*0.6) * cos(w[i].angle * (180/M_PI)));
            w[i].initialVelocityy = ((calculateDistance(350, 560, mx, my)*0.6) * sin(w[i].angle * (180/M_PI)));

            w[i].dx = w[i].initialVelocityx * t;
            w[i].dy = ((w[i].initialVelocityy * t) + (40.0 * pow(t, 2)));
        }

        if (i == prevI && !mstate){
                w[i].posx += w[i].dx * 0.12;
                w[i].posy -= w[i].dy * 0.12;
                w[i].dy -= 3;
        } else if (i != prevI){
            prevI = i;
            clicked = false;
        }
    }

            //good

            /*

            if (mx < 350 && my > 560){
                w[i].posx += w[i].dx * 0.12;
                w[i].posy -= w[i].dy * 0.12;
                w[i].dy -= 3;
            }

            else if (mx < 350 && my < 560){
                w[i].posx += w[i].dx * 0.12;
                w[i].posy += w[i].dy * 0.12;
                w[i].dy += 3;
            }
            else if (mx > 350 && my < 560){
                w[i].posx -= w[i].dx * 0.12;
                w[i].posy += w[i].dy * 0.12;
                w[i].dy += 3;
            }

            else if (mx > 350 && my > 560){
                w[i].posx -= w[i].dx * 0.12;
                w[i].posy -= w[i].dy * 0.12;
                w[i].dy -= 3;
            }
            */


    al_draw_rotated_bitmap(bottle[i], 10, 5, w[i].posx, w[i].posy, ((M_PI/4)*r), 0);

    pstate = mstate;

}

void moveBin(Motion &r, Motion w[], ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i, bool &f){

    if (isCollision(w, r, bottle, bin, i)){
        r.dx += 1.0;
        //setting a max speed of 20 pixels per second
        if (r.dx > 20.0){
            r.dx = 20.0;
        }
    }

    if (f && r.posx < 1640 && r.posx >= 1140){
        r.posx += r.dx;
    } else if (f && r.posx >= 1640){
        f = false;
        r.posx -= 12;
    }

    if (!f && r.posx > 1140 && r.posx <= 1640){
        r.posx -= r.dx;
    } else if (!f && r.posx <= 1140){
        f = true;
        r.posx += 12;
    }

    al_draw_bitmap(bin, r.posx,  r.posy, 0);

}





