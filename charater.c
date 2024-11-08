#include "charater.h"
#include "initialize.h"
#include "global.h"
// the state of character
enum {MOVE = 0, JUMP};
enum {LEFT = 0, RIGHT};
ALLEGRO_SAMPLE *sample = NULL;
float acc;
struct character{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
};

struct character chara;
int high, scene, space, freefall;
float indoor, jump_force;

void charater_process(ALLEGRO_EVENT event){
    if(level!=1) acc = 1.3;//initail acc=1.3,demo=0.8
    else if(bikeget==1) acc=0.8;
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
            if (key_state[ALLEGRO_KEY_SPACE] && !freefall){
                if(space == 0) space = 1;
                if(jump_force == 0) jump_force = 10;
                jump_force+=0.3;
                if(jump_force >= 25) jump_force = 25;
            }
            if(stand_on_block(level, sceneNum-2, 2) && indoor < 5){
                if(level == 0 || level == 1)indoor += 0.05;
                else if(level == 2 && toyget == 1) indoor += 0.05;
                else if(level == 3 && toyget == 2) indoor += 0.05;
            }
            else if(indoor > 0) indoor -= 0.05;
        }
    }

    // process the keyboard event
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ) key_state[event.keyboard.keycode] = true;
    if( event.type == ALLEGRO_EVENT_KEY_UP ) key_state[event.keyboard.keycode] = false;
    if( !key_state[ALLEGRO_KEY_SPACE] && space == 1 ) space = 2;
    if( mouse_in(10,10,120,57) == 2) judge_next_window = 11;
    if (indoor >= 5){
        judge_next_window = 11;
        if(level == 0 && pass == 0) pass++;
        else if(level == 1 && pass == 1) pass++;
        else if(level == 2 && pass == 2) pass++;
        else if(level == 3 && pass == 3){
            v_play();//play end_anime
            pass++;
        }
    }
}

void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_A] || key_state[ALLEGRO_KEY_LEFT] ){
        chara.dir = LEFT;
        if(chara.x>=5)chara.x -= 5;
        if(!freefall && !stand()) gravity();
    }
    if( key_state[ALLEGRO_KEY_D] || key_state[ALLEGRO_KEY_RIGHT]){
        chara.dir = RIGHT;
        if(chara.x<=800-chara.width-5)chara.x += 5;
        if(!freefall && !stand()) gravity();
    }
    if( space == 2 && !freefall ) gravity();
    else if( key_state[ALLEGRO_KEY_S] || key_state[ALLEGRO_KEY_DOWN] ){
        chara.y += 5;
        if(!freefall && !stand()) gravity();
    }
    img_change();
}

void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == MOVE )
    {
        if( chara.dir == LEFT )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
        else if( chara.dir == RIGHT )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else if(chara.state == JUMP){
        if( chara.dir == LEFT ){
            if( chara.anime < chara.anime_time/2 )
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0); // change image when jumping and (press L or R)
            else
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
        }
        else if( chara.dir == RIGHT ){
            if( chara.anime < chara.anime_time/2 )
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
}

void jump_draw(){
    sceneChange();
    game_scene_draw();//COVER THE SHADOW
    al_flip_display();
    al_wait_for_event(event_queue, &event);
    charater_process(event);
    charater_update();
    character_draw();
    al_flip_display();
}

void gravity(){
    freefall++;
    chara.state = JUMP;
    if(space != 2)
        jump_force = 0;
    for(float i=1;i>0;i+=0.2){
        high=(jump_force * 0.6/acc-(i+1));
        if(high > 25) high = 25;
        if(high < -25) high = -25;
        if(stand()) break;
        if(highest > chara.y - scene * 1000)
            highest = chara.y - scene * 1000;

        chara.y -= high;
        jump_draw();
    }
    freefall--;
    space=0;
    jump_force =0;
    chara.state = MOVE;
}

void sceneChange(){
    if(chara.y - high < -chara.height){
        scene++;
        high = chara.y + chara.height - high;
        chara.y = 900-chara.height;
    }

    if(chara.y - high > 1000 + chara.height && scene != 0){
        scene--;
        high = chara.y - high - 1000 - chara.height;
        chara.y = 0-chara.height;
    }
}

int stand(){
    for(int i = 0; i < blockNum ; i++){
       if(fall_on_block(i)){
            chara.y = blk[level][scene][i][1]-chara.height+5;
            if((chara.y - scene * 1000) - highest > 400) {
               heart--;
               if(level==0) al_play_sample_instance(sound1);
                else al_play_sample_instance(sound2);

          }
            highest = chara.y;
            jump_draw();
            return 1;
        }
    }
    if(chara.y >= 950-chara.height && high <= 0 && scene == 0){
        chara.y = 950-chara.height;
        if((chara.y - scene * 1000) - highest > 400)
        {   heart--;
           if(level==0) al_play_sample_instance(sound1);
            else    al_play_sample_instance(sound2);
        }
       highest = chara.y;
        al_flip_display();
        return 1;
    }
    return 0;
}

int fall_on_block(int i){
    if(high <= 0 && chara.x > blk[level][scene][i][0]-chara.width && chara.x < blk[level][scene][i][0] + block_w &&
        chara.y - high >= blk[level][scene][i][1]-chara.height+5 && chara.y <= blk[level][scene][i][1]-chara.height+5)
        return 1;
    return 0;
}

int stand_on_block(int l, int s, int i){
    if(l != level ) return 0;
    if(s != scene ) return 0;
    if(chara.x > blk[l][s][i][0]-chara.width && chara.x < blk[l][s][i][0] + block_w &&
        chara.y == blk[l][s][i][1]-chara.height+5)
        return 1;
    return 0;
}

void img_change(){
    if(stand_on_block(1,0,5) && bikeget == 0 ){
        bikeget = 1;
        acc=1.5;
        chara.img_move[0] = al_load_bitmap("./image/char_bike1.png");
        chara.img_move[1] = al_load_bitmap("./image/char_bike2.png");
        chara.width = al_get_bitmap_width(chara.img_move[0]);
        chara.height = al_get_bitmap_height(chara.img_move[0]);
    }
    if(stand_on_block(2,0,5) && toyget == 0){
        toyget = 1;
        chara.img_move[0] = al_load_bitmap("./image/char_toyget1.png");
        chara.img_move[1] = al_load_bitmap("./image/char_toyget2.png");
        chara.width = al_get_bitmap_width(chara.img_move[0]);
        chara.height = al_get_bitmap_height(chara.img_move[0]);
    }
    if(stand_on_block(3,1,3) && toyget == 1){
        toyget = 2;
        chara.img_move[0] = al_load_bitmap("./image/char_withcat1.png");
        chara.img_move[1] = al_load_bitmap("./image/char_withcat2.png");
        chara.width = al_get_bitmap_width(chara.img_move[0]);
        chara.height = al_get_bitmap_height(chara.img_move[0]);
    }
if(stand_on_block(0,0,7) && trapped[0] == 0){
        heart--;
        trapped[0] = 1;
        al_play_sample_instance(sound1);
    }
    if(stand_on_block(0,0,4) && trapped[1] == 0){
        heart--;
        trapped[1] = 1;
        al_play_sample_instance(sound1);
    }
    if(stand_on_block(0,1,5) && trapped[2] == 0){
        heart--;
        trapped[2] = 1;
        al_play_sample_instance(sound1);
    }
    if(stand_on_block(0,1,9) && trapped[3] == 0){
        heart--;
        trapped[3] = 1;
        al_play_sample_instance(sound1);
    }
    for(int i = 0 ; i < 4; i++){
        char temp[50];
        if(trapped[i]) sprintf( temp, "./image/trapped%d.png", i );
        else sprintf( temp, "./image/trap%d.png", i );
        trap[i] = al_load_bitmap(temp);
    }
}


