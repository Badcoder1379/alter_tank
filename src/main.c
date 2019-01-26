//
// Created by asus on 24/12/2018.
//\

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "structs.c"
#include "functions.h"
#include "view.h"
#include <time.h>


#ifdef main
#undef main
#endif
int menu(){
    int a=0;  //0=exit   //1=new_game
    const double FPS = 90;
    int i=100;
    bool click_up=false;
    bool click_down=false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("ALTER_tank", 10, 10, 800, 600, SDL_WINDOW_MAXIMIZED);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    while (handle_event()) {
        int start_ticks = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);
        show_menu(renderer,i);

        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        if(keyState[SDL_SCANCODE_UP]){
            if(click_up==false)i--;
            click_up=true;
        } else{click_up=false;}
        if(keyState[SDL_SCANCODE_DOWN]){
            if(click_down==false)i++;
            click_down=true;
        }else{click_down=false;}
        if(keyState[SDL_SCANCODE_SPACE]){
            if(i%4==0){
                a=2;
                break;
            }
            if(i%4==1){
                a=1;
                break;
            }
            if(i%4==2){
                a=0;
                break;
            }
            if(i%4==3){
                a=0;
                break;
            }
        }
            SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000/FPS);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return a;
}
void run_game(int b){ //if b=1 new game // if b=2 load game
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("ALTER_tank", 10, 10, 800, 600, SDL_WINDOW_MAXIMIZED);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
          STATE *state1;
        state1 = malloc(sizeof(STATE));
        state_def(state1);
        Tank *tank1 = malloc(sizeof(Tank));
        tank1_def(tank1);
        Tank *tank2 = malloc(sizeof(Tank));
        tank2_def(tank2);
        Bullet *bullet_set = malloc(10 * sizeof(Bullet));
        bullet_def(bullet_set);
        Bullet *bullet_set2 = malloc(10 * sizeof(Bullet));
        bullet_def(bullet_set2);
        Map *map1 = malloc(sizeof(Map));
        map_def(map1);
        load_map(map1);
        tank_set_place(map1, tank1);
        tank_set_place(map1, tank2);
        if(b==2){
            //loading
        }
    const double FPS = 90;
    while (handle_event()) {
        int start_ticks = SDL_GetTicks();
        move_tank(tank1);
        fire_tank1(bullet_set,tank1);
        move_second_tank(tank2);
        fire_second_tank1(bullet_set2,tank2);
        bullet_reflection(map1,bullet_set);
        bullet_reflection(map1,bullet_set2);
        bullet_move(bullet_set);
        bullet_move(bullet_set2);
        physic_check(map1,tank1);
        physic_check(map1,tank2);
        SDL_SetRenderDrawColor(renderer, map1->main_color.red, map1->main_color.green, map1->main_color.blue,map1->main_color.a);
        SDL_RenderClear(renderer);
        draw_map(renderer,map1);
        view_tank(renderer, tank1);
        view_tank(renderer, tank2);
        view_bullet(renderer,bullet_set);
        view_bullet(renderer,bullet_set2);
        show_score(renderer,state1);
        SDL_RenderPresent(renderer);
        logic_handle(state1,map1,tank1,tank2,bullet_set,bullet_set2);
        if(save(state1,map1,tank1,tank2,bullet_set,bullet_set2)==1 )break;
        if(state1->win==true)break;
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    while (1) {
        int a = menu();
        if(a==0)break;
        if (a == 1)run_game(1);
        if(a==2)run_game(2);

    }
}


