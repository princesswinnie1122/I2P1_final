#include "global.h"
#include "charater.h"

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_SAMPLE *song;
extern ALLEGRO_SAMPLE *song2;
extern ALLEGRO_SAMPLE *over;
extern ALLEGRO_SAMPLE_INSTANCE *sample_instance;
extern ALLEGRO_FONT *font;
extern ALLEGRO_FONT *font2;
extern ALLEGRO_BITMAP *block;
extern ALLEGRO_BITMAP *energybar;
extern ALLEGRO_BITMAP *midbar;
extern ALLEGRO_BITMAP *endbar;
extern ALLEGRO_BITMAP *stone;
extern ALLEGRO_BITMAP *grass;
extern ALLEGRO_BITMAP *door;
extern ALLEGRO_BITMAP *cattoy;
extern ALLEGRO_BITMAP *cat;
extern ALLEGRO_BITMAP *trap[4];
extern ALLEGRO_BITMAP *hearts[4];
extern ALLEGRO_BITMAP *losescene;
extern ALLEGRO_BITMAP *menubtn;
extern ALLEGRO_BITMAP *bike;
extern ALLEGRO_BITMAP *dooropen[5];
extern ALLEGRO_BITMAP *windows[6];
extern ALLEGRO_BITMAP *locks;
extern ALLEGRO_SAMPLE_INSTANCE *sound1;
extern ALLEGRO_SAMPLE_INSTANCE *sound2;
extern ALLEGRO_SAMPLE_INSTANCE *over1;

void all_init();
void game_init();
void block_init();
void character_init();
void menu_init();
void game_scene_init();
