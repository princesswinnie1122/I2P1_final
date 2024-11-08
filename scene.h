#include "global.h"
#include "charater.h"
#include "key.h"
#include "initialize.h"

extern char tmp[5];
extern int t;

void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void game_scene_draw();
int mouse_in(int x1, int x2, int y1, int y2);
int mouse_in_circle(int x, int y, int r);
