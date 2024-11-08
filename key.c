#include "key.h"

char tmp[50];
int t = 0;

void keyboard_press(ALLEGRO_EVENT event){

    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(t != 16){
            if (event.mouse.y > 370 && event.mouse.y < 370 + 75)//0-9
                for(int i = 0; i <= 9; i++)
                    if (event.mouse.x > 96 + i * 62 && event.mouse.x < 96 + 49 + i * 62)
                        tmp[t++] = '0' + i;
            if (event.mouse.y > 463 && event.mouse.y < 463 + 75)//A-J
                for(int i = 0; i <= 9; i++)
                    if (event.mouse.x > 96 + i * 62 && event.mouse.x < 96 + 49 + i * 62)
                        tmp[t++] = 'A' + i;
            if (event.mouse.y > 557 && event.mouse.y < 557 + 75){//K
                for(int i = 0; i <= 7; i++)
                    if (event.mouse.x > 96 + i * 62 && event.mouse.x < 96 + 49 + i * 62)
                        tmp[t++] = 'K' + i;
                if (event.mouse.x > 96 + 8 * 62 && event.mouse.x < 96 + 49 + 8 * 62) tmp[t++] = '_';
                if (event.mouse.x > 96 + 9 * 62 && event.mouse.x < 96 + 49 + 9 * 62) tmp[t++] = '.';
            }
            if (event.mouse.y > 652 && event.mouse.y < 652 + 75){
                for(int i = 0; i <= 7; i++)
                    if (event.mouse.x > 96 + i * 62 && event.mouse.x < 96 + 49 + i * 62)
                        tmp[t++] = 'S' + i;
                if (event.mouse.x > 96 + 8 * 62 && event.mouse.x < 96 + 49 + 9 * 62)
                    tmp[t--] = '\0';
            }
        }
    }
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if(t != 16){
            for(int i = 0; i < 26; i++)
                if(event.keyboard.keycode == 1 + i)
                    tmp[t++] = 'A' + i;
            for(int i = 0; i < 10; i++)
                if(event.keyboard.keycode == ALLEGRO_KEY_0 + i || event.keyboard.keycode == ALLEGRO_KEY_PAD_0 + i )
                   tmp[t++] = '0' + i;
            if(event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP || event.keyboard.keycode == ALLEGRO_KEY_PAD_DELETE)
                tmp[t++] = '.';
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && t >= 1)
            tmp[t--] = '\0';
    }
    tmp[t] ='\0';
}

