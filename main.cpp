/*****************************************************************************
 *	Name:     asso-the-coder                                                 *
 *	Date:     17 January 2020                                                *
 *                                                                           *
 *	Purpose:  Main code for Plastania                                        *
 *	                                                                         *
 *	Usage:  A fun game that is meant to spread awareness regarding the impact*
 *          of plastic waste on our planet; promoting environmental          *
 *          sustainability to combat climate change                          *
 *	                                                                         *
 *	Revision History: Beta release was on 13 January 2020                    *
 *	                                                                         *
 *	Known Issues: When high score is entered, the user is unable to play again
                  due to a random glitch that does not redraw the recycling
                  bin. If this occurs, restart the game

                  Some random mouse positions yield glitchy trajectories. Try
                  to avoid them if possible.

 *	                                                                         *
 *****************************************************************************/
 //including libraries and headers
#include <iostream>
#include <stdio.h>
#include "defines.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

//including Allegro headers
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//declaring global variables to be used multiple times across the program
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_FONT *mainFont;
ALLEGRO_FONT *titleFont;

int main(int argc, char *argv[]) {

    //initializing Allegro and its features
    initializeAllegro(SCREEN_W, SCREEN_H, "Plastania", display, event_queue, timer, mainFont, titleFont);

    //playing music that loops all throughout the game
    playMusic();

    //declaring and initializing bitmaps
    ALLEGRO_BITMAP *scaryMonster = nullptr;
    ALLEGRO_BITMAP *blueSky = nullptr;
    ALLEGRO_BITMAP *wBottle[500] = {nullptr};
    ALLEGRO_BITMAP *garbageIsland = nullptr;
    ALLEGRO_BITMAP *greenBin = nullptr;
    ALLEGRO_BITMAP *cannonWheel = nullptr;
    ALLEGRO_BITMAP *cannon = nullptr;
    ALLEGRO_BITMAP *lifeHeart[5] = {nullptr};
    ALLEGRO_BITMAP *heroTurtles[3] = {nullptr};
    ALLEGRO_BITMAP *cannonPlatform = nullptr;

    //declaring and initializing audio samples
    ALLEGRO_SAMPLE *endGameSound = nullptr;
    ALLEGRO_SAMPLE *bottleInSound = nullptr;
    ALLEGRO_SAMPLE *bottleOutSound = nullptr;

    //loading all samples and bitmaps with files
    loadElements(scaryMonster, blueSky, wBottle, garbageIsland, greenBin, cannonWheel, cannon, lifeHeart, cannonPlatform, heroTurtles, endGameSound, bottleInSound, bottleOutSound);

    //declaring struct variables, some being arrays
    Motion water[500], recycle;
    User player[20];

    //initializing struct variables
    for (int i = 0; i < 500; i++){
        water[i].posx = 340;
        water[i].posy = 499;
        water[i].dx = 2.0;
        water[i].dy = 1.0;
    }
    recycle.posx = 1150;
    recycle.posy = 620;
    recycle.dx = 3.0;
    recycle.dy = 0.0;

    //declaring text file
    FILE *file;

    //declaring and initializing logistical variables for the program
    bool doExit = false;
    bool playGameAgain = true;
    bool mainTitleDisplay = true;
    bool handleHighScores = false;
    bool displayScoresTab = false;
    bool instructionsTab = false;
    bool creditsTab = false;
    bool forwardsBin = true;

    //declaring and initializing logistical mouse variables
    int mousex, mousey = 0;
    bool mouseState = false;
    bool prevMouseState = false;
    bool clicked = false;

    //declaring and initializing counters
    int time = 0;
    int bottleCounter = 0;
    int prevBC = 0;
    int lives = 5;
    int currentScore = 0;
    int playerCounter = 0;

    //main game loop
    while (!doExit){

            //waits for event queue to begin executing
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            //closes display
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                doExit = true;
            }

            //sets the mouse coordinates to variables
            if (ev.mouse.x > 0 && ev.mouse.x < SCREEN_W){
                mousex = ev.mouse.x;
            }
            if (ev.mouse.y > 0 && ev.mouse.y < SCREEN_H){
                mousey = ev.mouse.y;
            }

            //sets the mouse state (clicked or unclicked) to variables
            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                mouseState = true;
            }
            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                mouseState = false;
            }

            //timer works as a loop, increases all counters, withholds all game functionality
            if (ev.type == ALLEGRO_EVENT_TIMER){
                al_clear_to_color(BACKGROUND);
                //draws title display along with implementing its functionalities (buttons, etc.)
                if (mainTitleDisplay){
                    titleScreenDisplay(scaryMonster, mousex, mousey, mouseState, prevMouseState, mainTitleDisplay, instructionsTab, creditsTab);
                }
                //draws instructions/how-to-play along with implementing its functionalities (buttons, etc.)
                else if (instructionsTab){
                    howToPlay(mainTitleDisplay, instructionsTab, heroTurtles, mousex, mousey, mouseState, prevMouseState);
                }
                //draws credits along with implementing its functionalities (buttons, etc.)
                else if (creditsTab){
                    displayCredits(mainTitleDisplay, creditsTab, heroTurtles, mousex, mousey, mouseState, prevMouseState);
                }
                //sorts high scores in descending order and writes them to text file
                else if (handleHighScores){
                    sortHighScores(currentScore, player, playerCounter, file);
                    inputHighScores(currentScore, player, playerCounter, file, handleHighScores, displayScoresTab);
                }
                //displays high scores
                else if (displayScoresTab){
                    displayHighScores(player, playerCounter, displayScoresTab, mousex, mousey, mouseState, prevMouseState);
                }
                //loops game (resets counters), or ends game
                else if (!playGameAgain){
                    gameOver(scaryMonster, lives, playGameAgain, mousex, mousey, mouseState, prevMouseState, recycle,
                             bottleCounter, currentScore, doExit, handleHighScores);
                }

                //all remaining game functionality that occurs on the game screen
                else {
                    //draws game's stationary graphics
                    drawGameBitmaps(blueSky, cannon, garbageIsland, cannonWheel, cannonPlatform, heroTurtles);
                    //calculates trajectory of water bottle by calculating physically accurate projectile motion
                    calculateTrajectory(water, mousex, mousey, prevMouseState, mouseState, time, clicked, wBottle, bottleCounter, prevBC);
                    //displays score
                    al_draw_textf(mainFont, WHITE, 1700, 20, ALLEGRO_ALIGN_CENTRE, "Score: %d", currentScore);
                    //slingshot selection with boundaries; aids in projectile motion calculation
                    slingShot(mousex, mousey, mouseState, prevMouseState, clicked);
                    //moves recycling bin back and forth
                    moveBin(recycle, water, wBottle, greenBin, bottleCounter, forwardsBin);
                    //calculates dimensions of bounding boxes for collision detection
                    calcBounds(water, recycle, wBottle, greenBin, bottleCounter);

                    //the comment below is a call to a very useful function for debugging, however not part of the final implementation
                    //drawBoundingBox(water, recycle, wBottle, greenBin, bottleCounter);

                    //draws graphics based on user's lives
                    drawHearts(lives, lifeHeart);

                    //checks if there is a collision; increases counters and plays sound effects accordingly
                    if (isCollision(water, recycle, wBottle, greenBin, bottleCounter)){
                        al_play_sample(bottleInSound, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        bottleCounter += 1;
                        currentScore += 1;
                    //checks collision and bottle position; manipulates counters and plays sound effects accordingly
                    } else if ((water[bottleCounter].posy > 510 || water[bottleCounter].posx > 1940
                         || water[bottleCounter].posx < 0) && !isCollision(water, recycle, wBottle, greenBin, bottleCounter)){
                            al_play_sample(bottleOutSound, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            bottleCounter += 1;
                            lives -= 1;
                    }

                    /*checks if there are no more lives; plays sound effects accordingly; terminates game screen display; manipulates
                    logistical variables so that game keeps looping*/
                    if (lives == 0){
                        al_play_sample(endGameSound, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        playGameAgain = false;
                    }

                }
                //flipping display each frame
                al_flip_display();
            }
    }

    //convey success with no errors
    return 0;
}
