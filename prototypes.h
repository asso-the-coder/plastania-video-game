#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

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

const int SCREEN_W = 1920;       // screen width
const int SCREEN_H = 1030;       // screen height
const float FPS = 60;			// set frame rate

//declaring structure that includes all information regarding any graphics's motion
struct Motion {
    int posx;
    int posy;
    float dx;
    float dy;
    int initialVelocityx;
    int initialVelocityy;
    float angle;
    int bbRight, bbLeft, bbTop, bbBottom;
};

//declaring structure that includes all information regarding the user's username and their score
struct User {
    char username[20];
    int highscore;
};

int playMusic();

int initializeAllegro(int width, int height, const char title[], ALLEGRO_DISPLAY *&display,
            ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&arial, ALLEGRO_FONT *&minecraft);

int loadElements(ALLEGRO_BITMAP *&monster, ALLEGRO_BITMAP *&sky, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *&island, ALLEGRO_BITMAP *&bin,
    ALLEGRO_BITMAP *&wheel, ALLEGRO_BITMAP *&slingshot, ALLEGRO_BITMAP *heart[], ALLEGRO_BITMAP *&platform, ALLEGRO_BITMAP *turtles[],
    ALLEGRO_SAMPLE *&endGame, ALLEGRO_SAMPLE *&bottleIn, ALLEGRO_SAMPLE *&bottleOut);

void drawGameBitmaps(ALLEGRO_BITMAP *sky, ALLEGRO_BITMAP *slingshot, ALLEGRO_BITMAP *island, ALLEGRO_BITMAP *wheel, ALLEGRO_BITMAP *platform, ALLEGRO_BITMAP *turtles[]);

void titleScreenDisplay(ALLEGRO_BITMAP *monster, int mx, int my, bool &mstate, bool &pstate, bool &drawTitle, bool &instructions, bool &credits);

void howToPlay(bool &drawTitle, bool &instructions, ALLEGRO_BITMAP *turtles[], int mx, int my, bool &mstate, bool &pstate);

void displayCredits(bool &drawTitle, bool &credits, ALLEGRO_BITMAP *turtles[], int mx, int my, bool &mstate, bool &pstate);

void slingShot(int mx, int my, bool &mstate, bool &pstate, bool &clicked);

float calculateDistance(float x1, float y1, float x2, float y2);

void calculateTrajectory(Motion w[], int mx, int my, bool &pstate, bool &mstate, int t, bool &clicked,
             ALLEGRO_BITMAP *bottle[], int &i, int &prevI);

void moveBin(Motion &r, Motion w[], ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i, bool &f);

void calcBounds(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i);

void drawBoundingBox(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i);

bool isCollision(Motion w[], Motion &r, ALLEGRO_BITMAP *bottle[], ALLEGRO_BITMAP *bin, int i);

void drawHearts(int livesCounter, ALLEGRO_BITMAP *heart[]);

void gameOver(ALLEGRO_BITMAP *monster, int &livesCounter, bool &playAgain, int mx, int my, bool &mstate,
               bool &pstate, Motion &r, int &i, int &score, bool &doExit, bool &highScores);

int displayHighScores(User p[], int &counter, bool &displayScores, int mx, int my, bool &mstate, bool &pstate);

int sortHighScores(int score, User p[], int &counter, FILE *fptr);

int inputHighScores(int score, User p[], int &counter, FILE *fptr, bool &highScores, bool &displayScores);

#endif // PROTOTYPES_H_INCLUDED
