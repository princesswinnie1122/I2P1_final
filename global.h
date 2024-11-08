#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int heart;
extern int highest;
extern int judge_next_window;
extern int window;
extern int level;
extern int pass;
extern int scene;
extern int sceneNum;
extern int blockNum;
extern int ****blk;
extern int block_w;
extern int toyget;
extern int trapped[4];
extern int bikeget;
extern float indoor;
extern float jump_force;
extern float acc;
extern bool key_state[ALLEGRO_KEY_MAX];
extern ALLEGRO_BITMAP *energybar;
extern ALLEGRO_BITMAP *midbar;
extern ALLEGRO_BITMAP *endbar;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern ALLEGRO_EVENT event;
extern ALLEGRO_DISPLAY* display;
#endif
