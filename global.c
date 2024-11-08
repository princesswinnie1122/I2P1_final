#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 800;
const int HEIGHT = 1000;
int block_w;
int pass = 0;
int toyget = 0;
int bikeget=0;
int trapped[4] = {0};
int judge_next_window = 0;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
ALLEGRO_EVENT event;
bool key_state[ALLEGRO_KEY_MAX] = {false};
