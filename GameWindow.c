#include "GameWindow.h"
#include "scene.h"
bool draw = false;

// ALLEGRO Variables

int Game_establish() {
    int msg = 0;
    al_init();
    event_queue = al_create_event_queue();
    //v_play1();//begin anime
    all_init();
    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }
    return 0;
}

int game_run() {
    int error = 0;
    if( draw ) game_draw();
    draw = false;
    if (!al_is_event_queue_empty(event_queue))error = process_event();
    return error;
}
////""
void game_draw(){
    level = window % 10;
    if( window /10 == 1) menu_draw();//initial window=10
    else if( window / 10 == 2 )game_scene_draw();
    al_flip_display();
}

void window_change(){
    draw = true;
    if(window / 10 == 1) {
        // initialize next scene
        if( judge_next_window != 0 ){
            window = judge_next_window ;
            level = window % 10;
            judge_next_window = 0;
        }
        if(window / 10 == 2)
           character_init();
    }
    if(window / 10 == 2 && heart != 0 ){
        charater_update();
        if( judge_next_window == 11 ){ //stage->menu
            window = judge_next_window;
            judge_next_window = 0;
        }
    }
    if(window / 10 == 2 && heart == 0 ){
        v_play2();
        al_play_sample_instance(over1);
        judge_next_window = 19;
        window = judge_next_window;
        judge_next_window = 0;
        pass = toyget = bikeget = 0;
        for(int i = 0 ; i < 4; trapped[i++] = 0);
        heart=3; level=1;
    }

}

int process_event(){
    // Request the event
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( window / 10 == 1) menu_process(event);
    if( window / 10 == 2) {
        charater_process(event);

    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || (mouse_in(0,900,800,1000) ==2 && (window==11 ||window==10 || window==12)  ) )//press grass to exit the game
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            window_change();

    return 0;
}

