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

/** This function initializes Allegro and all its features
    The parameters for this function are the display, the event queue, the timer, fonts, screen dimensions, and the display title
    Returns a 0 if all good, -1 if there are errors like failure to initialize audio, reserve samples, or initialize codecs.
*/
int initializeAllegro(int width, int height, const char title[], ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue, ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&arial, ALLEGRO_FONT *&minecraft) {

    //initializes Allegro
	al_init();

	//initializes display and checks for errors
	display = al_create_display(width, height);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

	//sets title of display
	al_set_window_title(display, title);

   	//initializes keyboard routines and checks for errors
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	//adds image processor and checks for errors
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//installs audio and checks for errors
	if (!al_install_audio()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//adds audio processor and checks for errors
	if (!al_init_acodec_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio codecs!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//reserves samples and checks for errors
	if (!al_reserve_samples(4)){
        al_show_native_message_box(display, "Error", "Error", "Failed to reserve samples!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
    }

    //initializes fonts and checks for errors
    if (!al_init_font_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
	if (!al_init_ttf_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize ttf addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//loads fonts and checks for errors
    arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 80, 0);
    if (!arial){
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    minecraft = al_load_ttf_font("Minecrafter.Reg.ttf", 115, 0);
    if (!minecraft){
        al_show_native_message_box(display, "Error", "Error", "Could not load minecraft.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //initializes primitives addons and checks for errors
 	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	//creates timer in relation to frames per seoond rate and checks for errors
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
   	}

	//sets up event queue and checks for errors
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}


    //installs mouse and checks for errors
    if (!al_install_mouse()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

    //registers event sources
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//clears the display and flips it
	al_clear_to_color(BACKGROUND);
	al_flip_display();

	//starts timer
	al_start_timer(timer);

	//conveys success with no errors
	return 0;
}


