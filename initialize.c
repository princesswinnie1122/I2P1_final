#include "initialize.h"
#include "charater.h"
const char *title = "Final Project : Orange I'm coming !";


void all_init(){
    block_init();
    game_init();
    menu_init();
    game_scene_init();
}


int sceneNum = 3, blockNum = 11, ****blk;

void block_init(){
    srand(time(NULL));
    blk = (int****)malloc(sizeof(int***) * 4);
    for(int i = 0; i < 4; i++) {
        blk[i] = (int***)malloc(sizeof(int**) * sceneNum);
        for(int j = 0; j <sceneNum; j++){
            blk[i][j] = (int**)malloc(sizeof(int*) * blockNum);
            for(int k = 0; k < blockNum; k++){
                blk[i][j][k] = (int*)malloc(sizeof(int) * 2);
                blk[i][j][k][0] = rand() % 11 * 50 + 130;
                blk[i][j][k][1] = 80 * k + 40;
                if(j != 0) blk[i][j][k][1] += 40;//scene2底層
                if(j==2) blk[i][j][k][0]=-100;
            }
        }
        blk[i][sceneNum-2][0][1] = blk[i][sceneNum-2][1][1] = -100;//最後上面兩格
        }
}


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE *meow;
ALLEGRO_SAMPLE *idai;
ALLEGRO_SAMPLE *over;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
ALLEGRO_SAMPLE_INSTANCE *sound1;
ALLEGRO_SAMPLE_INSTANCE *sound2;
ALLEGRO_SAMPLE_INSTANCE *over1;
void game_init() {
    printf( "Game Initializing...\n" );
    al_init();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/gameicon.png");
    al_set_display_icon(display, icon);
    // Load sound
    song = al_load_sample("./sound/begin.wav");

    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
}

struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
};
int heart=3;
int highest;

void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        if(level == 0){
            sprintf( temp, "./image/cat_move%d.png", i );//stage1
        }
        else if(level==1 && bikeget==1)
                 sprintf( temp, "./image/char_bike%d.png", i );
        else{
            if(toyget == 0)
                sprintf( temp, "./image/char_move%d.png", i ); //stage2
            else if(toyget == 1)
                sprintf( temp, "./image/char_toyget%d.png", i ); //stage3 when toy get
            else if(toyget == 2)
                sprintf( temp, "./image/char_withcat%d.png", i ); //stage4 when cat get
        }
            chara.img_move[i-1] = al_load_bitmap(temp);
    }
    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    scene = 0;
    indoor = 0;
    highest = 950-chara.height;
    // load effective sound
    meow = al_load_sample("./sound/meow.wav");
    sound1  = al_create_sample_instance(meow);
    al_set_sample_instance_playmode(sound1, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sound1, al_get_default_mixer());

    idai = al_load_sample("./sound/idai.wav");
    sound2  = al_create_sample_instance(idai);
    al_set_sample_instance_playmode(sound2, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sound2, al_get_default_mixer());

    over = al_load_sample("./sound/0000.wav");
    over1  = al_create_sample_instance(over);
    al_set_sample_instance_playmode(over1, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(over1, al_get_default_mixer());

    chara.x = 300;
    chara.y = 950-chara.height;
    chara.dir = false;
    // initial the animation component
    chara.anime = 0;
    chara.anime_time = 30;

}


ALLEGRO_FONT *font;
ALLEGRO_FONT *font2;
ALLEGRO_BITMAP *windows[6];
ALLEGRO_BITMAP *locks;

void menu_init(){
    font = al_load_ttf_font("./font/Pattanakarn Medium.ttf",40,0);
    font2 = al_load_ttf_font("./font/Pattanakarn Medium.ttf",30,0);
    windows[0] = al_load_bitmap("./image/window10.png");//home
    windows[1] = al_load_bitmap("./image/window11.png");//menu
    windows[2] = al_load_bitmap("./image/window12.png");//save
    windows[3] = al_load_bitmap("./image/window13.png");//game crew
    windows[4] = al_load_bitmap("./image/window20.png");//game itself
    windows[5] = al_load_bitmap("./image/gameover.png");
    locks = al_load_bitmap("./image/lock.png");
}

ALLEGRO_BITMAP *block = NULL;
ALLEGRO_BITMAP *energybar = NULL;
ALLEGRO_BITMAP *midbar = NULL;
ALLEGRO_BITMAP *endbar = NULL;
ALLEGRO_BITMAP *stone = NULL;
ALLEGRO_BITMAP *grass = NULL;
ALLEGRO_BITMAP *door = NULL;
ALLEGRO_BITMAP *cattoy = NULL;
ALLEGRO_BITMAP *cat = NULL;
ALLEGRO_BITMAP *dooropen[5];
ALLEGRO_BITMAP *menubtn;
ALLEGRO_BITMAP *bike;
ALLEGRO_BITMAP *trap[4];
ALLEGRO_BITMAP *hearts[4];
ALLEGRO_BITMAP *losescene=NULL;
void game_scene_init(){
    block = al_load_bitmap("./image/block.png");
    energybar = al_load_bitmap("./image/energybar.png");
    midbar = al_load_bitmap("./image/energy.png");
    endbar = al_load_bitmap("./image/end.png");
    stone = al_load_bitmap("./image/stone.png");
    grass = al_load_bitmap("./image/grass.png");
    door = al_load_bitmap("./image/door.png");
    cat = al_load_bitmap("./image/cat.png");
    cattoy = al_load_bitmap("./image/cat_toy.png");
    menubtn = al_load_bitmap("./image/menubtn.png");
    losescene=al_load_bitmap("./image/losescene.png");
    bike=al_load_bitmap("./image/bike.png");
    // load door hearts images
    for(int i = 0 ; i< 5; i++){
        char temp[50];
        sprintf( temp, "./image/dooropen%d.png", i );
        dooropen[i] = al_load_bitmap(temp);
    }
    for(int i = 0 ; i < 4; i++){
        char temp[50];
        sprintf( temp, "./image/heart%d.png", i );
        hearts[i] = al_load_bitmap(temp);
    }
    for(int i = 0 ; i < 4; i++){
        char temp[50];
        if(trapped[i]) sprintf( temp, "./image/trapped%d.png", i );
        else sprintf( temp, "./image/trap%d.png", i );
        trap[i] = al_load_bitmap(temp);
    }
    block_w = al_get_bitmap_width(block);
}
