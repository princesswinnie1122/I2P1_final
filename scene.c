#include "scene.h"

int window = 10;
int level = 0;
int fps_tmp = 0;

// function of menu
char datas[50];
FILE *data;
int step = -5;

void menu_process(ALLEGRO_EVENT event){
    if(level == 0){
        if(mouse_in(272,833,423,900) == 2) //save
            judge_next_window = 12;
        if(mouse_in(15,695,231,824) == 2) // game crew
            judge_next_window = 13;
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && mouse_in_circle(730,45,100) != 1)
            judge_next_window = 11; //menu
        }
    if(level > 0 && mouse_in_circle(730,45,100) == 2){
        judge_next_window = 10; //home
        fps_tmp = 0;
    }

    if(level == 1){//menu
        if( mouse_in(110,345,452,438) == 2 )
            judge_next_window = 20;//stage1
        if( mouse_in(340,488,682,582) == 2 && pass > 0)
            judge_next_window = 21;
        if( mouse_in(110,632,452,725) == 2 && pass > 1)
            judge_next_window = 22;
        if( mouse_in(340,774,682,868) == 2 && pass > 2)
            judge_next_window = 23;
    }
    if(level == 2){//curent state:save
        if(step == -5){
            if(mouse_in(96,763,279,831) == 2) save_game();
            if(mouse_in(311,763,494,831) == 2) read_game();
            keyboard_press(event);
        }
        //after save or read
        if(mouse_in(180,440,300,480) == 2){  //yes
            if(step == -4){ //exists ,so read
                step = 1;
                read_game();
            }
            if(step == -3){ //please enter valid
                step = 0;
                read_game();
            }
            if(step == -2){ //overwrite
                step = 1;
                save_game();
            }
            if(step == -1){ //create
                  step = 0;
                save_game();
            }
        }
        if(mouse_in(350,440,470,480) == 2 && step >= -4 && step <= -1){//no
            step = 0;
            read_game();
        }

    }
    if(level==9) {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
            al_destroy_sample(over);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
            judge_next_window = 11; //menu
    }
}

int mouse_in(int x1, int y1, int x2, int y2){//rectangle
    if( event.mouse.x > x1 && event.mouse.x < x2 && event.mouse.y > y1 && event.mouse.y < y2){
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            return 2;
        return 1;
    }
    return 0;
}
int mouse_in_circle(int x, int y, int r){//circle
    if(((event.mouse.x-x)*(event.mouse.x-x) + (event.mouse.y-y)*(event.mouse.y-y)) < r * r){
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            return 2;
        return 1;
    }
    return 0;
}

void menu_draw(){
    if(level == 0){// window/10
        if(fps_tmp % 40 == 0 && fps_tmp % 80 != 0 || fps_tmp == 0)
            al_draw_bitmap(windows[0],0,0,0);
        al_flip_display();
        if(fps_tmp % 80 == 0)
            al_draw_filled_rectangle(114, 445, 711, 559, al_map_rgb(42,44,65));//cover words
    }
    if( event.type == ALLEGRO_EVENT_TIMER )
        if( event.timer.source == fps )
            fps_tmp++;
    if(level == 1){//lock
        al_draw_bitmap(windows[1],0,0,0);
        if( pass < 1 )
            al_draw_bitmap(locks,647,545,0);
        if( pass < 2 )
            al_draw_bitmap(locks,417,688,0);
        if( pass < 3 )
            al_draw_bitmap(locks,647,831,0);
    }
    if(level == 2){
        al_draw_bitmap(windows[2],0,0,0);
        al_draw_text(font, al_map_rgb(255,255,255), 400, 150 , ALLEGRO_ALIGN_CENTRE, tmp);//draw tmp[]
        if(step == -4 || step == -2){
            al_draw_rectangle(158,314,642,506,al_map_rgb(255,255,255),6);
            al_draw_filled_rectangle(158,314,642,506, al_map_rgb(42,44,65));
            al_draw_text(font2,al_map_rgb(255,255,255),180,325,0,"The save exists.");//first line
        }
        if(step == -3 || step == -1){
            al_draw_rectangle(158,314,642,506,al_map_rgb(255,255,255),6);
            al_draw_filled_rectangle(158,314,642,506, al_map_rgb(42,44,65));//42,44,65 = background
            al_draw_text(font2,al_map_rgb(255,255,255),180,320,0,"The save doesn't exist.");//first line
        }
        if(step == -4) al_draw_text(font2,al_map_rgb(255,255,255),180,370,0,"Do you want to Read.");//second line
        if(step == -3) al_draw_text(font2,al_map_rgb(255,255,255),180,370,0,"Please enter valid Save.");
        if(step == -2) al_draw_text(font2,al_map_rgb(255,255,255),180,370,0,"Do you want to Overwrite.");
        if(step == -1) al_draw_text(font2,al_map_rgb(255,255,255),180,370,0,"Do you want to Create.");
        if(step == -4 || step == -2 || step == -1){
            al_draw_rectangle(180,440,300,480,al_map_rgb(255,255,255),4);
            al_draw_text(font2,al_map_rgb(255,255,255),240,428,1,"YES");//third line
            al_draw_rectangle(350,440,470,480,al_map_rgb(255,255,255),4);
            al_draw_text(font2,al_map_rgb(255,255,255),410,428,1,"NO");
        }
        if(step == -3){
            al_draw_rectangle(180,440,300,480,al_map_rgb(255,255,255),4);
            al_draw_text(font2,al_map_rgb(255,255,255),240,428,1,"OK");//third line
            al_draw_rectangle(350,440,470,480,al_map_rgb(255,255,255),4);
            al_draw_text(font2,al_map_rgb(255,255,255),410,428,1,"FINE");
        }

    }
    if(level == 3)
        al_draw_bitmap(windows[3],0,0,0);
    if(level == 9)
        al_draw_bitmap(windows[5],0,0,0);

    al_flip_display();

}


void game_scene_draw(){
    al_draw_bitmap(windows[4], 0, 0, 0);
    al_draw_bitmap(menubtn, 10, 10, 0);
    for(int i = 0; i < blockNum; i++)
        al_draw_bitmap(block, blk[level][scene][i][0], blk[level][scene][i][1], 0);
    if(scene == 0){
        al_draw_bitmap(stone, 0, 950, 0);
        al_draw_bitmap(grass, 0, 930, 0);
    }
    if(scene == 0)
        al_draw_bitmap(door, 300+20, 950-100,0);
    if(scene == sceneNum-2 && indoor <= 5)
        al_draw_bitmap(dooropen[(int)indoor], blk[level][scene][2][0]+20, blk[level][scene][2][1]-100,0);
    if(level == 0){
        if(scene == 0){
            al_draw_bitmap(trap[0], blk[level][scene][7][0]+20, blk[level][scene][7][1]-50, 0);
            al_draw_bitmap(trap[1], blk[level][scene][4][0]+20, blk[level][scene][4][1]-50, 0);
        }
        else{
            al_draw_bitmap(trap[2], blk[level][scene][5][0]+20, blk[level][scene][5][1]-50, 0);
            al_draw_bitmap(trap[3], blk[level][scene][9][0]+20, blk[level][scene][9][1]-50, 0);
        }
    }
    if(level == 1 && scene == 0 && bikeget == 0)
        al_draw_bitmap(bike, blk[level][scene][5][0], blk[level][scene][5][1]-56,0);
    if(level == 2 && scene == 0 && toyget == 0)
        al_draw_bitmap(cattoy, blk[level][scene][5][0], blk[level][scene][5][1]-56,0);
    if(level == 3 && scene == 1 && toyget == 1)
        al_draw_bitmap(cat, blk[level][scene][3][0] + 10 , blk[level][scene][3][1]-80,0);
    al_draw_bitmap(energybar, 15, 250, 0);
    for(int i = 10; i <= (int)jump_force; i++){
        if(i != jump_force) al_draw_bitmap(midbar, 15, 250+(25-i)/1*24, 0);
        else al_draw_bitmap(endbar, 15, 250+(25-i)/1*24, 0);
    }
    al_draw_bitmap(hearts[heart], 13, 69, 0);
    character_draw();
}

void save_game(){
    if(step == -5)sprintf(datas, "./data/%s.txt",tmp);
    if((data = fopen(datas, "r")) != false && step == -5)
        step = -2;  //save file ,file exist
    else if(step == -5)
        step = -1;//save file ,file not exist
    if(step == 1){ //save
        fclose(data);
        data = fopen(datas, "w");
        fprintf(data,"%d %d",toyget ,pass);
        fclose(data);
        step = -5;
        for(t; t > 0; tmp[--t] = '\0');
    }else if(step == 0){ //not save
        fclose(data);
        data = fopen(datas, "w");
        fprintf(data,"%d %d",toyget ,pass);
        fclose(data);
        step = -5;
        for(t; t > 0; tmp[--t] = '\0');
    }
}

void read_game(){
    if(step == -5)sprintf(datas, "./data/%s.txt",tmp);
    if((data = fopen(datas, "r")) != false && step == -5)
        step = -4; //file exist
    else if(step == -5)
        step = -3;
    if(step == 1){
        fscanf(data,"%d %d",&toyget ,&pass);
        fclose(data);
        step = -5;
        for(t; t > 0; tmp[--t] = '\0');
    }else if(step == 0){
        fclose(data);
        step = -5;
        for(t; t > 0; tmp[--t] = '\0');
    }

}
